#include "luckyxxl.hpp"


struct Distribute2 : Module {
	enum ParamIds {
		NUM_PARAMS
	};
	enum InputIds {
		DIST1_IN,
		DIST2_IN,
		DIST3_IN,
		DIST4_IN,
		DIST5_IN,
		DIST6_IN,
		DIST7_IN,
		DIST8_IN,
		DIST9_IN,
		DIST10_IN,
		NUM_INPUTS
	};
	enum OutputIds {
		DIST1_OUT1,
		DIST1_OUT2,
		DIST2_OUT1,
		DIST2_OUT2,
		DIST3_OUT1,
		DIST3_OUT2,
		DIST4_OUT1,
		DIST4_OUT2,
		DIST5_OUT1,
		DIST5_OUT2,
		DIST6_OUT1,
		DIST6_OUT2,
		DIST7_OUT1,
		DIST7_OUT2,
		DIST8_OUT1,
		DIST8_OUT2,
		DIST9_OUT1,
		DIST9_OUT2,
		DIST10_OUT1,
		DIST10_OUT2,
		NUM_OUTPUTS
	};

	Distribute2() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS) {}
	void step() override;
};


void Distribute2::step() {
	const float in1 = inputs[DIST1_IN].value;
	const float in2 = inputs[DIST2_IN].value;
	const float in3 = inputs[DIST3_IN].value;
	const float in4 = inputs[DIST4_IN].value;
	const float in5 = inputs[DIST5_IN].value;
	const float in6 = inputs[DIST6_IN].value;
	const float in7 = inputs[DIST7_IN].value;
	const float in8 = inputs[DIST8_IN].value;
	const float in9 = inputs[DIST9_IN].value;
	const float in10 = inputs[DIST10_IN].value;

	outputs[DIST1_OUT1].value = in1;
	outputs[DIST1_OUT2].value = in1;
	outputs[DIST2_OUT1].value = in2;
	outputs[DIST2_OUT2].value = in2;
	outputs[DIST3_OUT1].value = in3;
	outputs[DIST3_OUT2].value = in3;
	outputs[DIST4_OUT1].value = in4;
	outputs[DIST4_OUT2].value = in4;
	outputs[DIST5_OUT1].value = in5;
	outputs[DIST5_OUT2].value = in5;
	outputs[DIST6_OUT1].value = in6;
	outputs[DIST6_OUT2].value = in6;
	outputs[DIST7_OUT1].value = in7;
	outputs[DIST7_OUT2].value = in7;
	outputs[DIST8_OUT1].value = in8;
	outputs[DIST8_OUT2].value = in8;
	outputs[DIST9_OUT1].value = in9;
	outputs[DIST9_OUT2].value = in9;
	outputs[DIST10_OUT1].value = in10;
	outputs[DIST10_OUT2].value = in10;
}


Distribute2Widget::Distribute2Widget() {
	Distribute2 *module = new Distribute2();
	setModule(module);
	box.size = Vec(105, 380);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/Distribute2.svg")));
		addChild(panel);
	}

	addChild(createScrew<ScrewSilver>(Vec(box.size.x-15, 0)));
	addChild(createScrew<ScrewSilver>(Vec(15, 365)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x-30, 365)));

	addInput(createInput<PJ301MPort>(Vec(15.5, 40), module, Distribute2::DIST1_IN));
	addOutput(createOutput<PJ301MPort>(Vec(3, 65), module, Distribute2::DIST1_OUT1));
	addOutput(createOutput<PJ301MPort>(Vec(28, 65), module, Distribute2::DIST1_OUT2));
	addInput(createInput<PJ301MPort>(Vec(65.5, 40), module, Distribute2::DIST2_IN));
	addOutput(createOutput<PJ301MPort>(Vec(53, 65), module, Distribute2::DIST2_OUT1));
	addOutput(createOutput<PJ301MPort>(Vec(78, 65), module, Distribute2::DIST2_OUT2));
	addInput(createInput<PJ301MPort>(Vec(15.5, 105), module, Distribute2::DIST3_IN));
	addOutput(createOutput<PJ301MPort>(Vec(3, 130), module, Distribute2::DIST3_OUT1));
	addOutput(createOutput<PJ301MPort>(Vec(28, 130), module, Distribute2::DIST3_OUT2));
	addInput(createInput<PJ301MPort>(Vec(65.5, 105), module, Distribute2::DIST4_IN));
	addOutput(createOutput<PJ301MPort>(Vec(53, 130), module, Distribute2::DIST4_OUT1));
	addOutput(createOutput<PJ301MPort>(Vec(78, 130), module, Distribute2::DIST4_OUT2));
	addInput(createInput<PJ301MPort>(Vec(15.5, 170), module, Distribute2::DIST5_IN));
	addOutput(createOutput<PJ301MPort>(Vec(3, 195), module, Distribute2::DIST5_OUT1));
	addOutput(createOutput<PJ301MPort>(Vec(28, 195), module, Distribute2::DIST5_OUT2));
	addInput(createInput<PJ301MPort>(Vec(65.5, 170), module, Distribute2::DIST6_IN));
	addOutput(createOutput<PJ301MPort>(Vec(53, 195), module, Distribute2::DIST6_OUT1));
	addOutput(createOutput<PJ301MPort>(Vec(78, 195), module, Distribute2::DIST6_OUT2));
	addInput(createInput<PJ301MPort>(Vec(15.5, 235), module, Distribute2::DIST7_IN));
	addOutput(createOutput<PJ301MPort>(Vec(3, 260), module, Distribute2::DIST7_OUT1));
	addOutput(createOutput<PJ301MPort>(Vec(28, 260), module, Distribute2::DIST7_OUT2));
	addInput(createInput<PJ301MPort>(Vec(65.5, 235), module, Distribute2::DIST8_IN));
	addOutput(createOutput<PJ301MPort>(Vec(53, 260), module, Distribute2::DIST8_OUT1));
	addOutput(createOutput<PJ301MPort>(Vec(78, 260), module, Distribute2::DIST8_OUT2));
	addInput(createInput<PJ301MPort>(Vec(15.5, 300), module, Distribute2::DIST9_IN));
	addOutput(createOutput<PJ301MPort>(Vec(3, 325), module, Distribute2::DIST9_OUT1));
	addOutput(createOutput<PJ301MPort>(Vec(28, 325), module, Distribute2::DIST9_OUT2));
	addInput(createInput<PJ301MPort>(Vec(65.5, 300), module, Distribute2::DIST10_IN));
	addOutput(createOutput<PJ301MPort>(Vec(53, 325), module, Distribute2::DIST10_OUT1));
	addOutput(createOutput<PJ301MPort>(Vec(78, 325), module, Distribute2::DIST10_OUT2));
}


struct Distribute4 : Module {
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

	Distribute4() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS) {}
	void step() override;
};


void Distribute4::step() {
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


Distribute4Widget::Distribute4Widget() {
	Distribute4 *module = new Distribute4();
	setModule(module);
	box.size = Vec(105, 380);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/Distribute4.svg")));
		addChild(panel);
	}

	addChild(createScrew<ScrewSilver>(Vec(box.size.x-15, 0)));
	addChild(createScrew<ScrewSilver>(Vec(15, 365)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x-30, 365)));

	addInput(createInput<PJ301MPort>(Vec(40.5, 40), module, Distribute4::DIST1_IN));
	addOutput(createOutput<PJ301MPort>(Vec(3, 65), module, Distribute4::DIST1_OUT1));
	addOutput(createOutput<PJ301MPort>(Vec(28, 65), module, Distribute4::DIST1_OUT2));
	addOutput(createOutput<PJ301MPort>(Vec(53, 65), module, Distribute4::DIST1_OUT3));
	addOutput(createOutput<PJ301MPort>(Vec(78, 65), module, Distribute4::DIST1_OUT4));
	addInput(createInput<PJ301MPort>(Vec(40.5, 105), module, Distribute4::DIST2_IN));
	addOutput(createOutput<PJ301MPort>(Vec(3, 130), module, Distribute4::DIST2_OUT1));
	addOutput(createOutput<PJ301MPort>(Vec(28, 130), module, Distribute4::DIST2_OUT2));
	addOutput(createOutput<PJ301MPort>(Vec(53, 130), module, Distribute4::DIST2_OUT3));
	addOutput(createOutput<PJ301MPort>(Vec(78, 130), module, Distribute4::DIST2_OUT4));
	addInput(createInput<PJ301MPort>(Vec(40.5, 170), module, Distribute4::DIST3_IN));
	addOutput(createOutput<PJ301MPort>(Vec(3, 195), module, Distribute4::DIST3_OUT1));
	addOutput(createOutput<PJ301MPort>(Vec(28, 195), module, Distribute4::DIST3_OUT2));
	addOutput(createOutput<PJ301MPort>(Vec(53, 195), module, Distribute4::DIST3_OUT3));
	addOutput(createOutput<PJ301MPort>(Vec(78, 195), module, Distribute4::DIST3_OUT4));
	addInput(createInput<PJ301MPort>(Vec(40.5, 235), module, Distribute4::DIST4_IN));
	addOutput(createOutput<PJ301MPort>(Vec(3, 260), module, Distribute4::DIST4_OUT1));
	addOutput(createOutput<PJ301MPort>(Vec(28, 260), module, Distribute4::DIST4_OUT2));
	addOutput(createOutput<PJ301MPort>(Vec(53, 260), module, Distribute4::DIST4_OUT3));
	addOutput(createOutput<PJ301MPort>(Vec(78, 260), module, Distribute4::DIST4_OUT4));
	addInput(createInput<PJ301MPort>(Vec(40.5, 300), module, Distribute4::DIST5_IN));
	addOutput(createOutput<PJ301MPort>(Vec(3, 325), module, Distribute4::DIST5_OUT1));
	addOutput(createOutput<PJ301MPort>(Vec(28, 325), module, Distribute4::DIST5_OUT2));
	addOutput(createOutput<PJ301MPort>(Vec(53, 325), module, Distribute4::DIST5_OUT3));
	addOutput(createOutput<PJ301MPort>(Vec(78, 325), module, Distribute4::DIST5_OUT4));
}
