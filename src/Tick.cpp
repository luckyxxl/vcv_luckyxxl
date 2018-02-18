#include "luckyxxl.hpp"

#include "SevenSegmentDisplay.hpp"


struct Tick : Module {
	enum ParamIds {
		BPM,
		NUM_PARAMS
	};
	enum InputIds {
		NUM_INPUTS
	};
	enum OutputIds {
		OUT_1_1,
		OUT_1_2,
		OUT_1_4,
		OUT_1_8,
		OUT_1_4_3,
		OUT_1_16,
		OUT_1_8_3,
		NUM_OUTPUTS
	};

	Tick() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS) {}
	void step() override;

	float clock_phase = 0.f;
	uint32_t tick = 0u;

	char display[4];
};

void Tick::step() {
	const float bpm = params[BPM].value;
	const float bpm_display = std::round(bpm * 10.f) / 10.f;

	display[0] = int(bpm_display / 100.f) % 10 + '0';
	display[1] = int(bpm_display / 10.f) % 10 + '0';
	display[2] = int(bpm_display / 1.f) % 10 + '0';
	display[3] = int(bpm_display / .1f) % 10 + '0';
	if(display[0] == '0') display[0] = '\0';

	bool ticked = false;

	clock_phase += (bpm / 60.f) * engineGetSampleTime() * 12.f;

	if(clock_phase >= 1.f) {
		ticked = true;
		tick = (tick+1u) % 48u;
		clock_phase -= 1.f;
	}

	if(ticked) {
		outputs[OUT_1_1].value   = tick % 48u ? 0.f : 5.f;
		outputs[OUT_1_2].value   = tick % 24u ? 0.f : 5.f;
		outputs[OUT_1_4].value   = tick % 12u ? 0.f : 5.f;
		outputs[OUT_1_8].value   = tick % 6u ? 0.f : 5.f;
		outputs[OUT_1_4_3].value = tick % 4u ? 0.f : 5.f;
		outputs[OUT_1_16].value  = tick % 3u ? 0.f : 5.f;
		outputs[OUT_1_8_3].value = tick % 2u ? 0.f : 5.f;
	} else {
		outputs[OUT_1_1].value   = 0.f;
		outputs[OUT_1_2].value   = 0.f;
		outputs[OUT_1_4].value   = 0.f;
		outputs[OUT_1_8].value   = 0.f;
		outputs[OUT_1_4_3].value = 0.f;
		outputs[OUT_1_16].value  = 0.f;
		outputs[OUT_1_8_3].value = 0.f;
	}
}


struct TickWidget : ModuleWidget {
	TickWidget(Tick *module);
};

TickWidget::TickWidget(Tick *module) : ModuleWidget(module) {
	box.size = Vec(90, 380);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(pluginLuckyxxl, "res/Tick.svg")));
		addChild(panel);
	}

	addChild(Widget::create<ScrewSilver>(Vec(box.size.x-30, 0)));
	addChild(Widget::create<ScrewSilver>(Vec(15, 365)));
	addChild(Widget::create<ScrewSilver>(Vec(box.size.x-30, 365)));

	addChild(new SevenSegmentDisplay(Vec(14, 48), 5.f, &module->display[0]));
	addChild(new SevenSegmentDisplay(Vec(31, 48), 5.f, &module->display[1]));
	addChild(new SevenSegmentDisplay(Vec(48, 48), 5.f, &module->display[2]));
	addChild(new SevenSegmentDisplay(Vec(65, 48), 5.f, &module->display[3]));
	addChild(new SevenSegmentDot(Vec(61.5, 68), 5.f));

	addParam(ParamWidget::create<Davies1900hBlackKnob>(Vec(27, 80), module, Tick::BPM, 30.0, 240.0, 120.0));

	addOutput(Port::create<PJ301MPort>(Vec(47, 145), Port::OUTPUT, module, Tick::OUT_1_1));
	addOutput(Port::create<PJ301MPort>(Vec(47, 175), Port::OUTPUT, module, Tick::OUT_1_2));
	addOutput(Port::create<PJ301MPort>(Vec(47, 205), Port::OUTPUT, module, Tick::OUT_1_4));
	addOutput(Port::create<PJ301MPort>(Vec(47, 235), Port::OUTPUT, module, Tick::OUT_1_8));
	addOutput(Port::create<PJ301MPort>(Vec(47, 265), Port::OUTPUT, module, Tick::OUT_1_4_3));
	addOutput(Port::create<PJ301MPort>(Vec(47, 295), Port::OUTPUT, module, Tick::OUT_1_16));
	addOutput(Port::create<PJ301MPort>(Vec(47, 325), Port::OUTPUT, module, Tick::OUT_1_8_3));
}


Model *modelTickModule = Model::create<Tick, TickWidget>("luckyxxl", "Tick", "Tick", CLOCK_TAG);
