#include "Application.h"
int main(int argc, char* argv[]) 
{ 
	Application app = Application();
	return app.Run();
}
#if TRACY_ENABLE
void* operator new(std::size_t count)
{
	if (count == 0)
		++count;
	void* ptr = malloc(count);
	TracyAlloc(ptr, count);
	if(ptr) return ptr;
	throw std::bad_alloc{};
}
void operator delete(void* ptr) noexcept
{
	TracyFree(ptr);
	free(ptr);
}
#endif




