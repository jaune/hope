#ifndef HOPE_SAMPLES_TOY_LOGIC_PATH_H
#define HOPE_SAMPLES_TOY_LOGIC_PATH_H

#include "./action.h"

#include "../systems/TheGrid.h"


#include <profile.h>


namespace logic {
	namespace path {

		struct PathData {
			hope::grid::PathCrawler* crawler;
			hope::grid::Location current;
		};

		static std::map<PathId, PathData> gMap;
		

		PathId create(EntityId from_id, EntityId to_id){
			static PathId gIdCounter = 1;

			auto crawler = systems::TheGrid()->findShortestPathToAdjacent(from_id, to_id);

			if (crawler == NULL) {
				return 0;
			}

			PathId id = gIdCounter++;

			PathData data;

			data.crawler = crawler;

			gMap.insert(std::map<PathId, PathData>::value_type(id, data));
			return id;
		}

		bool next(PathId path_id) {
			auto it = gMap.find(path_id);

			if (it == gMap.end()){
				return false;
			}

			

			if (!systems::TheGrid()->navigation->validatePathCrawler(*it->second.crawler)){
				return false;
			}

			if (it->second.crawler->empty()){
				return false;
			}

			it->second.crawler->pop(it->second.current);

			return true;
		}

		hope::grid::Location current(PathId path_id) {
			auto it = gMap.find(path_id);

			assert(it != gMap.end());
			assert(it->second.crawler != NULL);

			return it->second.current;
		}

		bool empty(PathId path_id){
			auto it = gMap.find(path_id);

			assert(it != gMap.end());
			assert(it->second.crawler != NULL);

			return it->second.crawler->empty();
		}
		
		void destroy(PathId path_id) {
			auto it = gMap.find(path_id);

			assert(it != gMap.end());

			if (it->second.crawler != NULL) {
				delete it->second.crawler;
			}

			gMap.erase(it);
		}

	}
}


#endif /* HOPE_SAMPLES_TOY_LOGIC_PATH_H */