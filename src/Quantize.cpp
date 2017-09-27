#include "luckyxxl.hpp"

#include <map>


struct SevenSegmentDisplay : Widget {
	SevenSegmentDisplay(Vec position, char *display);

	void draw(NVGcontext *vg);

	Vec position;
	char *display;
};

SevenSegmentDisplay::SevenSegmentDisplay(Vec position, char *display)
	: position(position), display(display) {
}

static void drawSegment(NVGcontext *vg, const NVGcolor &color) {
	nvgBeginPath(vg);
	nvgMoveTo(vg, 0.f, 0.f);
	nvgLineTo(vg, .5f, .5f);
	nvgLineTo(vg, 1.5f, .5f);
	nvgLineTo(vg, 2.f, 0.f);
	nvgLineTo(vg, 1.5f, -.5f);
	nvgLineTo(vg, .5f, -.5f);
	nvgClosePath(vg);

	nvgFillColor(vg, color);
	nvgFill(vg);
}

#define BITMAP(a, b, c, d, e, f, g) (uint8_t)(a | b << 1 | c << 2 | d << 3 | e << 4 | f << 5 | g << 6)

static const std::map<char, uint8_t> bitmaps = {
	std::make_pair('c', BITMAP(1, 1, 0, 0, 1, 0, 1)),
	std::make_pair('d', BITMAP(0, 0, 1, 1, 1, 1, 1)),
	std::make_pair('e', BITMAP(1, 1, 0, 1, 1, 0, 1)),
	std::make_pair('f', BITMAP(1, 1, 0, 1, 1, 0, 0)),
	std::make_pair('g', BITMAP(1, 1, 1, 1, 0, 1, 1)),
	std::make_pair('a', BITMAP(1, 1, 1, 1, 1, 1, 0)),
	std::make_pair('b', BITMAP(0, 1, 0, 1, 1, 1, 1)),
	std::make_pair('#', BITMAP(0, 1, 1, 1, 1, 1, 0)),
};

#undef BITMAP

void SevenSegmentDisplay::draw(NVGcontext *vg) {
	nvgSave(vg);

	nvgTranslate(vg, position.x, position.y);
	nvgScale(vg, 10.f, 10.f);

	static const NVGcolor off_color = nvgRGB(0, 30, 0);
	static const NVGcolor on_color = nvgRGB(0, 200, 0);

	uint8_t bitmap = 0u;
	{
		auto b = bitmaps.find(*display);
		if(b != bitmaps.end()) bitmap = b->second;
	}

	drawSegment(vg, (bitmap & (1 << 0)) ? on_color : off_color);
	nvgTranslate(vg, 0.f, 2.f);
	drawSegment(vg, (bitmap & (1 << 3)) ? on_color : off_color);
	nvgTranslate(vg, 0.f, 2.f);
	drawSegment(vg, (bitmap & (1 << 6)) ? on_color : off_color);

	nvgTranslate(vg, 0.f, -4.f);
	nvgRotate(vg, NVG_PI/2.f);

	drawSegment(vg, (bitmap & (1 << 1)) ? on_color : off_color);
	nvgTranslate(vg, 0.f, -2.f);
	drawSegment(vg, (bitmap & (1 << 2)) ? on_color : off_color);

	nvgTranslate(vg, 2.f, 2.f);

	drawSegment(vg, (bitmap & (1 << 4)) ? on_color : off_color);
	nvgTranslate(vg, 0.f, -2.f);
	drawSegment(vg, (bitmap & (1 << 5)) ? on_color : off_color);

	nvgRestore(vg);
}


struct Quantize : Module {
	enum ParamIds {
		NUM_PARAMS
	};
	enum InputIds {
		IN,
		NUM_INPUTS
	};
	enum OutputIds {
		OUT,
		NUM_OUTPUTS
	};

	std::array<char, 2> display;

	Quantize();
	void step();

	void update_display(float o, float s);
};


Quantize::Quantize() {
	params.resize(NUM_PARAMS);
	inputs.resize(NUM_INPUTS);
	outputs.resize(NUM_OUTPUTS);

	display.fill('\0');
}

void Quantize::step() {
	const float in = getf(inputs[IN]);

	const float o = std::floor(in);
	const float s = std::floor((in - o) * 12.f);

	const float out = o + s / 12.f;

	setf(outputs[OUT], out);

	update_display(o, s);
}

void Quantize::update_display(float of, float sf) {
	//const int o = (int)of;
	const int s = (int)sf;

	static const std::array<char, 2> notes[12] = {
		{'c', '\0'},
		{'c', '#'},
		{'d', '\0'},
		{'d', '#'},
		{'e', '\0'},
		{'f', '\0'},
		{'f', '#'},
		{'g', '\0'},
		{'g', '#'},
		{'a', '\0'},
		{'a', '#'},
		{'b', '\0'},
	};

	display = notes[s];
}


QuantizeWidget::QuantizeWidget() {
	Quantize *module = new Quantize();
	setModule(module);
	box.size = Vec(105, 380);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load("plugins/luckyxxl/res/Quantize.svg"));
		addChild(panel);
	}

	addChild(createScrew<ScrewSilver>(Vec(box.size.x-30, 0)));
	addChild(createScrew<ScrewSilver>(Vec(15, 365)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x-30, 365)));

	addInput(createInput<PJ301MPort>(Vec(15, 320), module, Quantize::IN));
	addOutput(createOutput<PJ301MPort>(Vec(65, 320), module, Quantize::OUT));

	addChild(new SevenSegmentDisplay(Vec(20, 50), &module->display[0]));
	addChild(new SevenSegmentDisplay(Vec(60, 50), &module->display[1]));
}
