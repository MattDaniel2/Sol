#include <telem_stream.cpp>
#include <music.cpp>

int main() {
	std::thread thr_d(telem_stream);
	std::thread thr_f(music_spaceflight);

	thr_d.join();
	thr_f.join();
}
