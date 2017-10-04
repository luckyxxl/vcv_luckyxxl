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
		OUT_1_12,
		OUT_1_16,
		OUT_1_24,
		NUM_OUTPUTS
	};

	Tick();
	void step();

	float clock_phase = 0.f;
	uint32_t tick = UINT32_MAX;
	
	char display[4];
};


Tick::Tick() {
	params.resize(NUM_PARAMS);
	inputs.resize(NUM_INPUTS);
	outputs.resize(NUM_OUTPUTS);
}

void Tick::step() {
	const float bpm = params[BPM];

	display[0] = (int)(bpm / 100.f) % 10 + '0';
	display[1] = (int)(bpm / 10.f) % 10 + '0';
	display[2] = (int)(bpm / 1.f) % 10 + '0';
	display[3] = (int)(bpm / .1f) % 10 + '0';
	if(display[0] == '0') display[0] = '\0';

	clock_phase += (bpm / 60.f) / gSampleRate * 48;

	bool ticked = false;

	if(clock_phase >= 1.f) {
		ticked = true;
		if(++tick >= 192u) tick = 0u;
		clock_phase -= 1.f;
	}

	if(ticked) {
		setf(outputs[OUT_1_1], !(tick % 192u));
		setf(outputs[OUT_1_2], !(tick % 96u));
		setf(outputs[OUT_1_4], !(tick % 48u));
		setf(outputs[OUT_1_8], !(tick % 24u));
		setf(outputs[OUT_1_12], !(tick % 16u));
		setf(outputs[OUT_1_16], !(tick % 12u));
		setf(outputs[OUT_1_24], !(tick % 8u));
	} else {
		setf(outputs[OUT_1_1], 0.f);
		setf(outputs[OUT_1_2], 0.f);
		setf(outputs[OUT_1_4], 0.f);
		setf(outputs[OUT_1_8], 0.f);
		setf(outputs[OUT_1_12], 0.f);
		setf(outputs[OUT_1_16], 0.f);
		setf(outputs[OUT_1_24], 0.f);
	}
}


TickWidget::TickWidget() {
	Tick *module = new Tick();
	setModule(module);
	box.size = Vec(90, 380);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load("plugins/luckyxxl/res/Tick.svg"));
		addChild(panel);
	}

	addChild(createScrew<ScrewSilver>(Vec(box.size.x-30, 0)));
	addChild(createScrew<ScrewSilver>(Vec(15, 365)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x-30, 365)));
	
	addChild(new SevenSegmentDisplay(Vec(14, 48), 5.f, &module->display[0]));
	addChild(new SevenSegmentDisplay(Vec(31, 48), 5.f, &module->display[1]));
	addChild(new SevenSegmentDisplay(Vec(48, 48), 5.f, &module->display[2]));
	addChild(new SevenSegmentDisplay(Vec(65, 48), 5.f, &module->display[3]));
	addChild(new SevenSegmentDot(Vec(61.5, 68), 5.f));
	
	addParam(createParam<Davies1900hBlackKnob>(Vec(27, 80), module, Tick::BPM, 30.0, 240.0, 120.0));

	addOutput(createOutput<PJ301MPort>(Vec(55, 145), module, Tick::OUT_1_1));
	addOutput(createOutput<PJ301MPort>(Vec(55, 175), module, Tick::OUT_1_2));
	addOutput(createOutput<PJ301MPort>(Vec(55, 205), module, Tick::OUT_1_4));
	addOutput(createOutput<PJ301MPort>(Vec(55, 235), module, Tick::OUT_1_8));
	addOutput(createOutput<PJ301MPort>(Vec(55, 265), module, Tick::OUT_1_12));
	addOutput(createOutput<PJ301MPort>(Vec(55, 295), module, Tick::OUT_1_16));
	addOutput(createOutput<PJ301MPort>(Vec(55, 325), module, Tick::OUT_1_24));
}
