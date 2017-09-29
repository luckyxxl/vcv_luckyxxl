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

#define BITMAP(a, b, c, d, e, f, g) (uint8_t)(a << 0 | b << 1 | c << 2 | d << 3 | e << 4 | f << 5 | g << 6)

static const std::map<char, uint8_t> bitmaps = {
	std::make_pair('#', BITMAP(0, 1, 1, 1, 1, 1, 0)),
	std::make_pair('a', BITMAP(1, 1, 1, 1, 1, 1, 0)),
	std::make_pair('b', BITMAP(0, 1, 0, 1, 1, 1, 1)),
	std::make_pair('c', BITMAP(1, 1, 0, 0, 1, 0, 1)),
	std::make_pair('d', BITMAP(0, 0, 1, 1, 1, 1, 1)),
	std::make_pair('e', BITMAP(1, 1, 0, 1, 1, 0, 1)),
	std::make_pair('f', BITMAP(1, 1, 0, 1, 1, 0, 0)),
	std::make_pair('g', BITMAP(1, 1, 1, 1, 0, 1, 1)),
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

	#define BIT(x) (bitmap & 1 << x) ? on_color : off_color

	drawSegment(vg, BIT(0));
	nvgTranslate(vg, 0.f, 2.f);
	drawSegment(vg, BIT(3));
	nvgTranslate(vg, 0.f, 2.f);
	drawSegment(vg, BIT(6));

	nvgTranslate(vg, 0.f, -4.f);
	nvgRotate(vg, NVG_PI/2.f);

	drawSegment(vg, BIT(1));
	nvgTranslate(vg, 0.f, -2.f);
	drawSegment(vg, BIT(2));

	nvgTranslate(vg, 2.f, 2.f);

	drawSegment(vg, BIT(4));
	nvgTranslate(vg, 0.f, -2.f);
	drawSegment(vg, BIT(5));

	#undef BIT

	nvgRestore(vg);
}


struct Quantize : Module {
	enum ParamIds {
		DISPLAY_MODE,
		HOLD,
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

	int display_semi;
	std::array<char, 2> display;

	Quantize();
	void initialize();

	void step();

	void update_display();

	json_t *toJson() {
		json_t *r = json_object();
		json_object_set_new(r, "display_semi", json_integer(display_semi));
		return r;
	}

	void fromJson(json_t *r) {
		json_t *d = json_object_get(r, "display_semi");
		if(d) display_semi = json_integer_value(d);
	}
};


Quantize::Quantize() {
	params.resize(NUM_PARAMS);
	inputs.resize(NUM_INPUTS);
	outputs.resize(NUM_OUTPUTS);

	initialize();
}

void Quantize::initialize() {
	display_semi = 0;
	display.fill('\0');
}

void Quantize::step() {
	const float in = getf(inputs[IN]);

	const float o = std::floor(in);
	const float s = std::floor((in - o) * 12.f);

	const float out = o + s / 12.f;

	setf(outputs[OUT], out);

	if(!params[HOLD]) display_semi = (int)s;
	update_display();
}

void Quantize::update_display() {
	static const std::array<char, 2> semis_sharp[12] = {
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

	static const std::array<char, 2> semis_flat[12] = {
		{'c', '\0'},
		{'d', 'b'},
		{'d', '\0'},
		{'e', 'b'},
		{'e', '\0'},
		{'f', '\0'},
		{'g', 'b'},
		{'g', '\0'},
		{'a', 'b'},
		{'a', '\0'},
		{'b', 'b'},
		{'b', '\0'},
	};

	display = (params[DISPLAY_MODE] ? semis_sharp : semis_flat)[display_semi];
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

	addParam(createParam<CKSS>(Vec(30, 110), module, Quantize::DISPLAY_MODE, 0, 1, 1));
	addParam(createParam<CKSS>(Vec(70, 110), module, Quantize::HOLD, 0, 1, 0));
}
