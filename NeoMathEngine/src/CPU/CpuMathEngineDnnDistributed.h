/* Copyright © 2017-2023 ABBYY
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
--------------------------------------------------------------------------------------------------------------*/

#pragma once

#include <vector>
#include <thread>
#include <atomic>
#include <NeoMathEngine/NeoMathEngine.h>

namespace NeoML {

class CMultiThreadDistributedCommunicator {
public:
	explicit CMultiThreadDistributedCommunicator( int n_threads );
	void AllReduce( const CFloatHandle& handle, int size );
	void Broadcast( const CFloatHandle& handle, int size, int root );
	void Abort() { isAbort.store(true, std::memory_order_release); }
private:
	std::vector<float*> handles;

	std::atomic<int> counter;
	std::atomic_bool waiting_flag;
	int n_threads;
	std::atomic_bool isAbort;

	// non-blocking barrier
	void barrier();
	// collects handles from all threads into the common array
	void collectHandles( const CFloatHandle& handle );
};

} // namespace NeoML
