#pragma once

#include "xmrstak/jconf.hpp"
#include "crypto/cryptonight.h"
#include "xmrstak/backend/miner_work.hpp"
#include "xmrstak/backend/iBackend.hpp"

#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <future>

namespace xmrstak
{
namespace cpu
{

class minethd : public iBackend
{
public:
	static std::vector<iBackend*> thread_starter(uint32_t threadOffset, miner_work& pWork);
	static bool self_test();

	typedef void (*cn_hash_fun)(const void*, size_t, void*, cryptonight_ctx*);

	static cn_hash_fun func_selector(bool bHaveAes, bool bNoPrefetch, xmrstak_algo algo);
	static bool thd_setaffinity(std::thread::native_handle_type h, uint64_t cpu_id);

	static cryptonight_ctx* minethd_alloc_ctx();

private:
	typedef void (*cn_hash_fun_multi)(const void*, size_t, void*, cryptonight_ctx**);
	static cn_hash_fun_multi func_multi_selector(size_t N, bool bHaveAes, bool bNoPrefetch, xmrstak_algo algo);

	minethd(miner_work& pWork, size_t iNo, int iMultiway, bool no_prefetch, int64_t affinity);

	template<uint32_t N>
	void multiway_work_main();

	template<size_t N>
	void prep_multiway_work(uint8_t *bWorkBlob, uint32_t **piNonce);

	void work_main();
	void double_work_main();

	void original_3_work_main();
	void original_4_work_main();
	void original_5_work_main();
	void original_6_work_main();
	void original_7_work_main();
	void original_8_work_main();
	void original_9_work_main();
	void original_10_work_main();
	void original_11_work_main();
	void original_12_work_main();
	void original_13_work_main();
	void original_14_work_main();
	void original_15_work_main();

	void update_3_work_main();
	void update_4_work_main();
	void update_5_work_main();
	void update_6_work_main();
	void update_7_work_main();
	void update_8_work_main();
	void update_9_work_main();
	void update_10_work_main();
	void update_11_work_main();
	void update_12_work_main();
	void update_13_work_main();
	void update_14_work_main();
	void update_15_work_main();

	uint64_t iJobNo;

	miner_work oWork;

	std::promise<void> order_fix;
	std::mutex thd_aff_set;

	std::thread oWorkThd;
	int64_t affinity;

	bool bQuit;
	bool bNoPrefetch;
};

} // namespace cpu
} // namespace xmrstak
