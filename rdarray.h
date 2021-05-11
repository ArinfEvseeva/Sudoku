#ifndef _RDARRAY
	#include <cstdlib>
	#include <time.h>
	#define _RDARRAY
#endif

namespace sudoku{
	class rdarray{
		public:
			rdarray();
			void narray();
			int read(int i);

		private:
			int array[10];
			int rdseed;
	};
}
