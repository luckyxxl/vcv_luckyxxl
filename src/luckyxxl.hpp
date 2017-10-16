#include "rack.hpp"

#include <cmath>


using namespace rack;


extern Plugin *plugin;

////////////////////
// module widgets
////////////////////

struct DistributeWidget : ModuleWidget {
	DistributeWidget();
};

struct QuantizeWidget : ModuleWidget {
	QuantizeWidget();
};

struct TickWidget : ModuleWidget {
	TickWidget();
};
