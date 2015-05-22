#include "./profile.h"
#include <console.h>

#include <stdio.h>
#include <intrin.h>
#include <cassert>

#pragma intrinsic(__rdtsc)

namespace hope {
	
	namespace profile {

		typedef uint16_t SampleIndex;
		typedef uint16_t SampleLevel;

		const static size_t SAMPLE_MAX = 10000;

		struct Sample {
			Tick begin;
			Tick end;
			const char* name;

			SampleIndex parent;
			SampleLevel level;
		};

		static Sample gSamples[SAMPLE_MAX];
		
		static SampleIndex gActiveSampleIndex = 0;
		static SampleIndex gMaxSampleIndex = 0;

		void begin(const char* name) {
			assert(gMaxSampleIndex < SAMPLE_MAX);

			Sample& s = gSamples[gMaxSampleIndex];

			s.begin = __rdtsc();
			s.end = 0;
			s.name = name;
			s.parent = gActiveSampleIndex;
			
			if ((gActiveSampleIndex == 0) && (gMaxSampleIndex == 0)) {
				s.level = 0;
			}
			else {
				s.level = gSamples[gActiveSampleIndex].level + 1;
			}
			
			
			gActiveSampleIndex = gMaxSampleIndex;

			gMaxSampleIndex++;
		}

		void begin() {
			gActiveSampleIndex = 0;
			gMaxSampleIndex = 0;
			begin("<main>");
		}

				
		Tick end() {
			Sample& s = gSamples[gActiveSampleIndex];
			
			s.end = __rdtsc();

			gActiveSampleIndex = gSamples[gActiveSampleIndex].parent;

			return s.end - s.begin;
		}

		void log() {
			

			for (size_t i = 0; i < gMaxSampleIndex; ++i) {
				Tick total = gSamples[gSamples[i].parent].end - gSamples[gSamples[i].parent].begin;


				Tick e = gSamples[i].end - gSamples[i].begin;
				
				double pc = (double)e / (double)total;

				std::string tab;

				tab.append(gSamples[i].level * 2, ' ');
				
				hope::console::log("%s%s: %I64d mcycles (%.3f%%)", tab.c_str(), gSamples[i].name, e, pc);
			
			}


		}

	}
}