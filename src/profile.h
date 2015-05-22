namespace hope {
	namespace profile {

		typedef unsigned __int64 Tick;

		void begin();

		void begin(const char* name);
		
		Tick end();

		void log();

	}
}