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

	p->addModel(createModel<Distribute2Widget>("luckyxxl", "Distribute2", "Distribute2", MULTIPLE_TAG));
	p->addModel(createModel<Distribute4Widget>("luckyxxl", "Distribute", "Distribute4", MULTIPLE_TAG));
	p->addModel(createModel<QuantizeWidget>("luckyxxl", "Quantize", "Quantize", QUANTIZER_TAG));
	p->addModel(createModel<TickWidget>("luckyxxl", "Tick", "Tick", CLOCK_TAG));
}
