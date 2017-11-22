#include "luckyxxl.hpp"

#include "SevenSegmentDisplay.hpp"

#include <array>


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

	Quantize() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS) { reset(); }
	void reset() override;

	void step() override;

	void update_display();

	json_t *toJson() override {
		json_t *r = json_object();
		json_object_set_new(r, "display_semi", json_integer(display_semi));
		return r;
	}

	void fromJson(json_t *r) override {
		json_t *d = json_object_get(r, "display_semi");
		if(d) display_semi = json_integer_value(d);
	}
};


void Quantize::reset() {
	display_semi = 0;
	display.fill('\0');
}

void Quantize::step() {
	const float in = inputs[IN].value;

	const float o = std::floor(in);
	const float s = std::floor((in - o) * 12.f);

	const float out = o + s / 12.f;

	outputs[OUT].value = out;

	if(!params[HOLD].value) display_semi = s;
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

	display = (params[DISPLAY_MODE].value ? semis_sharp : semis_flat)[display_semi];
}


QuantizeWidget::QuantizeWidget() {
	Quantize *module = new Quantize();
	setModule(module);
	box.size = Vec(90, 380);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/Quantize.svg")));
		addChild(panel);
	}

	addChild(createScrew<ScrewSilver>(Vec(box.size.x-15, 0)));
	addChild(createScrew<ScrewSilver>(Vec(15, 365)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x-30, 365)));

	addInput(createInput<PJ301MPort>(Vec(12, 320), module, Quantize::IN));
	addOutput(createOutput<PJ301MPort>(Vec(53, 320), module, Quantize::OUT));

	addChild(new SevenSegmentDisplay(Vec(20, 49), 8.f, &module->display[0]));
	addChild(new SevenSegmentDisplay(Vec(52, 49), 8.f, &module->display[1]));

	addParam(createParam<CKSS>(Vec(24, 100), module, Quantize::DISPLAY_MODE, 0, 1, 1));
	addParam(createParam<CKSS>(Vec(60, 100), module, Quantize::HOLD, 0, 1, 0));
}
