#include "rack.hpp"

#include <cmath>


using namespace rack;


extern Plugin *plugin;

////////////////////
// module widgets
////////////////////

struct Distribute2Widget : ModuleWidget {
	Distribute2Widget();
};

struct Distribute4Widget : ModuleWidget {
	Distribute4Widget();
};

struct QuantizeWidget : ModuleWidget {
	QuantizeWidget();
};

struct TickWidget : ModuleWidget {
	TickWidget();
};
