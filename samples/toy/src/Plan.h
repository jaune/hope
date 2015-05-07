#ifndef HOPE_SAMPLES_TOY_PLAN_H
#define HOPE_SAMPLES_TOY_PLAN_H

#include "./ValueArray.h"

namespace plan {

	class Parameters{
	};

	class Condition{
	public:

		typedef bool(*Callback) (const plan::Condition& condition, const Parameters& parameters);
			

		const Callback callback;
		const char* label;

		Condition(const char* label, Callback callback) :
			label(label),
			callback(callback) {
		}

		void createPatameter() {
		}
	};




	class Action {
	public:

		enum Status {
			IN_PROGRESS = 0,
			SUCCESS,
			FAILURE
		};


		typedef Status(*Callback) (const plan::Action& action, const ValueArray& values);

		
		const char* label;
		const Callback callback;
		

		Action(const char* label, Callback callback) :
			label(label),
			callback(callback) {
		}	

		Status process(const ValueArray& v) const {
			return callback(*this, v);
		}
	};
		
	
	class Step {
	public:
		class Patameter {
		};

		typedef std::vector<Patameter*> PatameterVector;
		
		class Parametrable {
			PatameterVector parameters;
		public:
			void assignParameter(Patameter* p) {
				parameters.push_back(p);
			}
		};

		class Condition : public Parametrable {
		public:
			const plan::Condition* condition;
		
			Condition(const plan::Condition* condition) :
				condition(condition) {
			}			
		};

		class Action : public Parametrable {
		public:
			const plan::Action* action;
		
			Action(const plan::Action* action) :
				action(action) {
			}
		};

		typedef std::vector<Condition*> ConditionVector;
		
		

		PatameterVector parameters;
		ConditionVector preconditions;
		ConditionVector postconditions;
		Action* action;

		Step() :
			action(NULL) {
		}

		Patameter* createParameter() {
			Patameter *p = new Patameter();
			parameters.push_back(p);
			return p;
		}

		Condition* createPrecondition(const plan::Condition* condition) {
			Condition *p = new Condition(condition);
			preconditions.push_back(p);
			return p;
		}

		Condition* createPostcondition(const plan::Condition* condition) {
			Condition *p = new Condition(condition);
			postconditions.push_back(p);
			return p;
		}

		Action* createAction(const plan::Action* action) {
			if (this->action != NULL) {
				delete this->action;
			}
			this->action = new Action(action);
			return this->action;
		}
		
		bool hasPostcondition(const plan::Condition* condition) const {
			for (auto it = postconditions.begin(); it != postconditions.end(); ++it) {
				if ((*it)->condition == condition) {
					return true;
				}
			}
			return false;
		}
	};


	class Plan {
	public:
		class Step {
		public:
			const plan::Step* step;
			Step* nextStep;
			std::vector<size_t> parameters;

			Step(const plan::Step* step) :
				step(step),
				nextStep(NULL) {
			}

			void assignParameter(size_t index) {
				parameters.push_back(index);
			}
		};

		std::vector<Step*> steps;
		
		Step* firstStep;
		Step* lastStep;

		Plan() :
			firstStep(NULL),
			lastStep(NULL) {
		}

		Step* createStep(const plan::Step* step) {
			Step* s = new Step(step);
			
			steps.push_back(s);

			return s;
		}

		void defineFirstStep(Step* s){
			firstStep = s;
		}

		void defineLastStep(Step* s){
			lastStep = s;
		}
	};

	class Instance {
	public:
		enum Status {
			IN_PROGRESS,
			SUCCESS,
			FAILURE
		};

		ValueArray values;
		const Plan* plan;
		const Plan::Step* currentStep;

		Status status;
		bool is_complete;

		Instance(const Plan* plan, const ValueArray& values) :
			is_complete(false),
			plan(plan),
			values(values),
			status(IN_PROGRESS),
			currentStep(plan->firstStep) {
		}


		inline Status getStatus() const {
			return status;
		}
		
		inline bool isComplete () const {
			return is_complete;
		}

		void attachCurrentStepAction(EntityId agent_id) {
			
		}

		void process () {

			ValueArray v;

			for (auto it = currentStep->parameters.begin(); it != currentStep->parameters.end(); ++it) {
				v.push(*values.get(*it));
			}

			plan::Action::Status status = currentStep->step->action->action->process(v);

			if (status == plan::Action::SUCCESS) {
				currentStep = currentStep->nextStep;
				if (currentStep == NULL) {
					this->status = Status::SUCCESS;
					is_complete = true;
				}
			} else if (status == plan::Action::FAILURE) {
				this->status = Status::FAILURE;
				is_complete = true;
			}
		}
	};

	class Network {
		typedef std::vector<Step*> StepVector;
		typedef std::vector<Condition*> ConditionVector;
		typedef std::vector<Plan*> PlanVector;
		typedef std::vector<Action*> ActionVector;

		StepVector steps;
		ConditionVector conditions;
		PlanVector plans;
		ActionVector actions;

	public:
		Step* createStep(){
			Step* s = new Step();

			steps.push_back(s);

			return s;
		}

		Condition* createCondition(const char* name, Condition::Callback cb){
			Condition* s = new Condition(name, cb);

			conditions.push_back(s);

			return s;
		}

		Action* createAction(const char* name, Action::Callback cb){
			Action* a = new Action(name, cb);

			actions.push_back(a);

			return a;
		}

		Plan* createPlan() {
			Plan* p = new Plan();

			plans.push_back(p);

			return p;
		}

		Instance* createInstance(const Plan* plan, const ValueArray& values) {
			return new Instance(plan, values);
		}

		void destroyInstance(Instance* instance) {
			// TODO
		}

		void findPlan(const Step* finalStep, std::vector<const Plan*> &result) const {
			for (auto it = plans.begin(); it != plans.end(); ++it)  {
				if ((*it)->lastStep->step == finalStep){
					result.push_back((*it));
				}
			}
		}
		
		const Plan* findPlan(const Step* finalStep) const {
			std::vector<const Plan*> candidates;

			findPlan(finalStep, candidates);

			if (candidates.empty()) {
				return NULL;
			}
			
			return candidates.front();
		}


		
	};

};




#endif /* HOPE_SAMPLES_TOY_PLAN_H */