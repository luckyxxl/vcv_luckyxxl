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

	Distribute();
	void step();
};


Distribute::Distribute() {
	params.resize(NUM_PARAMS);
	inputs.resize(NUM_INPUTS);
	outputs.resize(NUM_OUTPUTS);
}

void Distribute::step() {
	if(inputs[DIST1_IN]) {
		setf(outputs[DIST1_OUT1], *inputs[DIST1_IN]);
		setf(outputs[DIST1_OUT2], *inputs[DIST1_IN]);
		setf(outputs[DIST1_OUT3], *inputs[DIST1_IN]);
		setf(outputs[DIST1_OUT4], *inputs[DIST1_IN]);
	}
	if(inputs[DIST2_IN]) {
		setf(outputs[DIST2_OUT1], *inputs[DIST2_IN]);
		setf(outputs[DIST2_OUT2], *inputs[DIST2_IN]);
		setf(outputs[DIST2_OUT3], *inputs[DIST2_IN]);
		setf(outputs[DIST2_OUT4], *inputs[DIST2_IN]);
	}
	if(inputs[DIST3_IN]) {
		setf(outputs[DIST3_OUT1], *inputs[DIST3_IN]);
		setf(outputs[DIST3_OUT2], *inputs[DIST3_IN]);
		setf(outputs[DIST3_OUT3], *inputs[DIST3_IN]);
		setf(outputs[DIST3_OUT4], *inputs[DIST3_IN]);
	}
	if(inputs[DIST4_IN]) {
		setf(outputs[DIST4_OUT1], *inputs[DIST4_IN]);
		setf(outputs[DIST4_OUT2], *inputs[DIST4_IN]);
		setf(outputs[DIST4_OUT3], *inputs[DIST4_IN]);
		setf(outputs[DIST4_OUT4], *inputs[DIST4_IN]);
	}
	if(inputs[DIST5_IN]) {
		setf(outputs[DIST5_OUT1], *inputs[DIST5_IN]);
		setf(outputs[DIST5_OUT2], *inputs[DIST5_IN]);
		setf(outputs[DIST5_OUT3], *inputs[DIST5_IN]);
		setf(outputs[DIST5_OUT4], *inputs[DIST5_IN]);
	}
}


DistributeWidget::DistributeWidget() {
	Distribute *module = new Distribute();
	setModule(module);
	box.size = Vec(15*6, 380);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load("plugins/luckyxxl/res/Distribute.svg"));
		addChild(panel);
	}

	addInput(createInput<PJ301MPort>(Vec(33, 30), module, Distribute::DIST1_IN));
	addOutput(createOutput<PJ301MPort>(Vec(0, 58), module, Distribute::DIST1_OUT1));
	addOutput(createOutput<PJ301MPort>(Vec(25, 58), module, Distribute::DIST1_OUT2));
	addOutput(createOutput<PJ301MPort>(Vec(50, 58), module, Distribute::DIST1_OUT3));
	addOutput(createOutput<PJ301MPort>(Vec(75, 58), module, Distribute::DIST1_OUT4));
	addInput(createInput<PJ301MPort>(Vec(33, 100), module, Distribute::DIST2_IN));
	addOutput(createOutput<PJ301MPort>(Vec(0, 128), module, Distribute::DIST2_OUT1));
	addOutput(createOutput<PJ301MPort>(Vec(25, 128), module, Distribute::DIST2_OUT2));
	addOutput(createOutput<PJ301MPort>(Vec(50, 128), module, Distribute::DIST2_OUT3));
	addOutput(createOutput<PJ301MPort>(Vec(75, 128), module, Distribute::DIST2_OUT4));
	addInput(createInput<PJ301MPort>(Vec(33, 170), module, Distribute::DIST3_IN));
	addOutput(createOutput<PJ301MPort>(Vec(0, 198), module, Distribute::DIST3_OUT1));
	addOutput(createOutput<PJ301MPort>(Vec(25, 198), module, Distribute::DIST3_OUT2));
	addOutput(createOutput<PJ301MPort>(Vec(50, 198), module, Distribute::DIST3_OUT3));
	addOutput(createOutput<PJ301MPort>(Vec(75, 198), module, Distribute::DIST3_OUT4));
	addInput(createInput<PJ301MPort>(Vec(33, 240), module, Distribute::DIST4_IN));
	addOutput(createOutput<PJ301MPort>(Vec(0, 268), module, Distribute::DIST4_OUT1));
	addOutput(createOutput<PJ301MPort>(Vec(25, 268), module, Distribute::DIST4_OUT2));
	addOutput(createOutput<PJ301MPort>(Vec(50, 268), module, Distribute::DIST4_OUT3));
	addOutput(createOutput<PJ301MPort>(Vec(75, 268), module, Distribute::DIST4_OUT4));
	addInput(createInput<PJ301MPort>(Vec(33, 310), module, Distribute::DIST5_IN));
	addOutput(createOutput<PJ301MPort>(Vec(0, 338), module, Distribute::DIST5_OUT1));
	addOutput(createOutput<PJ301MPort>(Vec(25, 338), module, Distribute::DIST5_OUT2));
	addOutput(createOutput<PJ301MPort>(Vec(50, 338), module, Distribute::DIST5_OUT3));
	addOutput(createOutput<PJ301MPort>(Vec(75, 338), module, Distribute::DIST5_OUT4));
}
