#include "luckyxxl.hpp"


Plugin *plugin;

void init(rack::Plugin *p) {
	plugin = p;
	p->slug = "luckyxxl";
#ifdef VERSION
	p->version = TOSTRING(VERSION);
#endif
	p->website = "https://github.com/luckyxxl/vcv_luckyxxl";
	p->manual = "https://github.com/luckyxxl/vcv_luckyxxl/blob/master/README.md";

	p->addModel(createModel<DistributeWidget>("luckyxxl", "Distribute", "Distribute", MULTIPLE_TAG));
	p->addModel(createModel<QuantizeWidget>("luckyxxl", "Quantize", "Quantize", QUANTIZER_TAG));
	p->addModel(createModel<TickWidget>("luckyxxl", "Tick", "Tick", CLOCK_TAG));
}
