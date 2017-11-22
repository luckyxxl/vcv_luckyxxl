#include "luckyxxl.hpp"


struct Distribute : Module {
	enum ParamIds {
		NUM_PARAMS
	};
	enum InputIds {
		DIST1_IN,
		DIST2_IN,
		DIST3_IN,
		DIST4_IN,
		DIST5_IN,
		NUM_INPUTS
	};
	enum OutputIds {
		DIST1_OUT1,
		DIST1_OUT2,
		DIST1_OUT3,
		DIST1_OUT4,
		DIST2_OUT1,
		DIST2_OUT2,
		DIST2_OUT3,
		DIST2_OUT4,
		DIST3_OUT1,
		DIST3_OUT2,
		DIST3_OUT3,
		DIST3_OUT4,
		DIST4_OUT1,
		DIST4_OUT2,
		DIST4_OUT3,
		DIST4_OUT4,
		DIST5_OUT1,
		DIST5_OUT2,
		DIST5_OUT3,
		DIST5_OUT4,
		NUM_OUTPUTS
	};

	Distribute() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS) {}
	void step() override;
};


void Distribute::step() {
	const float in1 = inputs[DIST1_IN].value;
	const float in2 = inputs[DIST2_IN].value;
	const float in3 = inputs[DIST3_IN].value;
	const float in4 = inputs[DIST4_IN].value;
	const float in5 = inputs[DIST5_IN].value;

	outputs[DIST1_OUT1].value = in1;
	outputs[DIST1_OUT2].value = in1;
	outputs[DIST1_OUT3].value = in1;
	outputs[DIST1_OUT4].value = in1;
	outputs[DIST2_OUT1].value = in2;
	outputs[DIST2_OUT2].value = in2;
	outputs[DIST2_OUT3].value = in2;
	outputs[DIST2_OUT4].value = in2;
	outputs[DIST3_OUT1].value = in3;
	outputs[DIST3_OUT2].value = in3;
	outputs[DIST3_OUT3].value = in3;
	outputs[DIST3_OUT4].value = in3;
	outputs[DIST4_OUT1].value = in4;
	outputs[DIST4_OUT2].value = in4;
	outputs[DIST4_OUT3].value = in4;
	outputs[DIST4_OUT4].value = in4;
	outputs[DIST5_OUT1].value = in5;
	outputs[DIST5_OUT2].value = in5;
	outputs[DIST5_OUT3].value = in5;
	outputs[DIST5_OUT4].value = in5;
}


DistributeWidget::DistributeWidget() {
	Distribute *module = new Distribute();
	setModule(module);
	box.size = Vec(105, 380);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/Distribute.svg")));
		addChild(panel);
	}

	addChild(createScrew<ScrewSilver>(Vec(box.size.x-30, 0)));
	addChild(createScrew<ScrewSilver>(Vec(15, 365)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x-30, 365)));

	addInput(createInput<PJ301MPort>(Vec(40.5, 40), module, Distribute::DIST1_IN));
	addOutput(createOutput<PJ301MPort>(Vec(3, 65), module, Distribute::DIST1_OUT1));
	addOutput(createOutput<PJ301MPort>(Vec(28, 65), module, Distribute::DIST1_OUT2));
	addOutput(createOutput<PJ301MPort>(Vec(53, 65), module, Distribute::DIST1_OUT3));
	addOutput(createOutput<PJ301MPort>(Vec(78, 65), module, Distribute::DIST1_OUT4));
	addInput(createInput<PJ301MPort>(Vec(40, 105), module, Distribute::DIST2_IN));
	addOutput(createOutput<PJ301MPort>(Vec(3, 130), module, Distribute::DIST2_OUT1));
	addOutput(createOutput<PJ301MPort>(Vec(28, 130), module, Distribute::DIST2_OUT2));
	addOutput(createOutput<PJ301MPort>(Vec(53, 130), module, Distribute::DIST2_OUT3));
	addOutput(createOutput<PJ301MPort>(Vec(78, 130), module, Distribute::DIST2_OUT4));
	addInput(createInput<PJ301MPort>(Vec(40, 170), module, Distribute::DIST3_IN));
	addOutput(createOutput<PJ301MPort>(Vec(3, 195), module, Distribute::DIST3_OUT1));
	addOutput(createOutput<PJ301MPort>(Vec(28, 195), module, Distribute::DIST3_OUT2));
	addOutput(createOutput<PJ301MPort>(Vec(53, 195), module, Distribute::DIST3_OUT3));
	addOutput(createOutput<PJ301MPort>(Vec(78, 195), module, Distribute::DIST3_OUT4));
	addInput(createInput<PJ301MPort>(Vec(40, 235), module, Distribute::DIST4_IN));
	addOutput(createOutput<PJ301MPort>(Vec(3, 260), module, Distribute::DIST4_OUT1));
	addOutput(createOutput<PJ301MPort>(Vec(28, 260), module, Distribute::DIST4_OUT2));
	addOutput(createOutput<PJ301MPort>(Vec(53, 260), module, Distribute::DIST4_OUT3));
	addOutput(createOutput<PJ301MPort>(Vec(78, 260), module, Distribute::DIST4_OUT4));
	addInput(createInput<PJ301MPort>(Vec(40, 300), module, Distribute::DIST5_IN));
	addOutput(createOutput<PJ301MPort>(Vec(3, 325), module, Distribute::DIST5_OUT1));
	addOutput(createOutput<PJ301MPort>(Vec(28, 325), module, Distribute::DIST5_OUT2));
	addOutput(createOutput<PJ301MPort>(Vec(53, 325), module, Distribute::DIST5_OUT3));
	addOutput(createOutput<PJ301MPort>(Vec(78, 325), module, Distribute::DIST5_OUT4));
}
