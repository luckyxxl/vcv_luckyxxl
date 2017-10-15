#include "luckyxxl.hpp"


Plugin *plugin;

void init(rack::Plugin *p) {
	plugin = p;
	plugin->slug = "luckyxxl";
	plugin->name = "luckyxxl";
	plugin->homepageUrl = "https://github.com/luckyxxl/vcv_luckyxxl";

	createModel<DistributeWidget>(plugin, "Distribute", "Distribute");
	createModel<QuantizeWidget>(plugin, "Quantize", "Quantize");
	createModel<TickWidget>(plugin, "Tick", "Tick");
}
