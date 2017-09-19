#include "luckyxxl.hpp"
#include <math.h>
#include "dsp.hpp"


struct LuckyxxlPlugin : Plugin {
	LuckyxxlPlugin() {
		slug = "luckyxxl";
		name = "luckyxxl";
		createModel<DistributeWidget>(this, "Distribute", "Distribute");
	}
};


Plugin *init() {
	return new LuckyxxlPlugin();
}
