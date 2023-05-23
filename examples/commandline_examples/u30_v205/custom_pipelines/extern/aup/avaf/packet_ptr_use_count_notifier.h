#pragma once

// std
#include <condition_variable>
#include <list>
#include <memory>
#include <mutex>
#include <thread>

// sdk
#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

// local
#include "aup/avaf/packet_ptr.h"
#include "aup/avaf/packets/packet_base.h"
#include "aup/avaf/thread_name.h"

namespace aup::avaf {

class PacketPtrUseCountNotifier
{
	std::mutex mux;
	struct Entry
	{
		std::condition_variable* convar;
		aup::avaf::PacketPtr<PacketBase> packet;
	};
	std::list<Entry> entries;
	boost::posix_time::milliseconds interval;
	std::unique_ptr<boost::asio::deadline_timer> timer;
	void io_service_worker()
	{
		AUP_AVAF_HANDLE_THREAD_NAME_EXT("PacketPtrUseCountNotifier");
		io_service.run();
	}
	boost::asio::io_service io_service;
	std::thread io_service_thread;
	bool running;
	void check_use_counts()
	{
		mux.lock();
		auto itr = entries.begin();
		int sz   = (int)entries.size();
		mux.unlock();
		for (int i = 0; i < sz; i++) {
			if (itr->packet.use_count() > 2) {
				itr++;
				continue;
			}
			auto convar = itr->convar;
			// if itr is not the last entry, lock is not necessary because we are using a linked-list
			if (i == sz - 1) {
				mux.lock();
			}
			itr = entries.erase(itr);
			if (i == sz - 1) {
				mux.unlock();
			}
			convar->notify_one();
		}
		if (!running) {
			return;
		}
		timer->expires_at(timer->expires_at() + interval);
		timer->async_wait(boost::bind(&PacketPtrUseCountNotifier::check_use_counts, this));
	}

public:
	PacketPtrUseCountNotifier(int interval) : interval(interval), running(true)
	{
		timer = std::make_unique<boost::asio::deadline_timer>(io_service, this->interval);
		timer->async_wait(boost::bind(&PacketPtrUseCountNotifier::check_use_counts, this));
		io_service_thread = std::thread([this] { this->io_service_worker(); });
	}
	~PacketPtrUseCountNotifier()
	{
		io_service.stop();
		running = false;
		io_service_thread.join();
	}
	void add_entry(std::condition_variable* convar, aup::avaf::PacketPtr<PacketBase> packet)
	{
		Entry entry({
		    .convar = convar,
		    .packet = packet,
		});
		{
			std::lock_guard<std::mutex> lg(mux);
			entries.push_back(entry);
		}
	}
};

} // namespace aup::avaf
