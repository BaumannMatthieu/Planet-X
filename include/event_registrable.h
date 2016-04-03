#ifndef __EVENT_REGISTRABLE_H__
#define __EVENT_REGISTRABLE_H__

class EventRegistrable {
	public:
		EventRegistrable() { };
		~EventRegistrable() { };

	private:
		virtual void register_events() = 0;
};

#endif
