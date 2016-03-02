#ifndef COINSHIELD_LLU_MACRO
#define COINSHIELD_LLU_MACRO

#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <string>
#include <stdarg.h>

#define LOCK(a) boost::lock_guard<boost::mutex> lock(a)

#define Sleep(a)            boost::this_thread::sleep(boost::posix_time::milliseconds(a))
#define loop                for(;;)


	/** Class the tracks the duration of time elapsed in seconds or milliseconds.
		Used for socket timers to determine time outs. **/
	class Timer
	{
	private:
		boost::posix_time::ptime TIMER_START, TIMER_END;
		bool fStopped = false;
	
	public:
		inline void Start() { TIMER_START = boost::posix_time::microsec_clock::local_time(); fStopped = false; }
		inline void Reset() { Start(); }
		inline void Stop() { TIMER_END = boost::posix_time::microsec_clock::local_time(); fStopped = true; }
		
		/** Return the Total Seconds Elapsed Since Timer Started. **/
		unsigned int Elapsed()
		{
			if(fStopped)
				return (TIMER_END - TIMER_START).total_seconds();
				
			return (boost::posix_time::microsec_clock::local_time() - TIMER_START).total_seconds();
		}
		
		/** Return the Total Milliseconds Elapsed Since Timer Started. **/
		unsigned int ElapsedMilliseconds()
		{
			if(fStopped)
				return (TIMER_END - TIMER_START).total_milliseconds();
				
			return (boost::posix_time::microsec_clock::local_time() - TIMER_START).total_milliseconds();
		}
	};
	
std::string real_strprintf(const std::string &format, int dummy, ...)
{
    char buffer[50000];
    char* p = buffer;
    int limit = sizeof(buffer);
    int ret;
    loop
    {
        va_list arg_ptr;
        va_start(arg_ptr, dummy);
        ret = _vsnprintf(p, limit, format.c_str(), arg_ptr);
        va_end(arg_ptr);
        if (ret >= 0 && ret < limit)
            break;
        if (p != buffer)
            delete[] p;
        limit *= 2;
        p = new char[limit];
        if (p == NULL)
            throw std::bad_alloc();
    }
    std::string str(p, p+ret);
    if (p != buffer)
        delete[] p;
    return str;
}

#define strprintf(format, ...) real_strprintf(format, 0, __VA_ARGS__)

#endif