// 02纤程.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <optional>
#include <coroutine>

template<typename T>

class SegmentedTask {

public:

	struct promise_type {

		SegmentedTask<T> get_return_object()

		{

			return SegmentedTask{ Handle::from_promise(*this) };

		}

		static std::suspend_never initial_suspend() noexcept { return {}; }

		static std::suspend_always final_suspend() noexcept { return {}; }

		std::suspend_always yield_value(std::nullopt_t) noexcept { return {}; }

		std::suspend_never return_value(T value) noexcept

		{

			returnValue = value;

			return {};

		}

		static void unhandled_exception() { throw; }

		std::optional<T> returnValue;

	};

	using Handle = std::coroutine_handle<promise_type>;

	explicit SegmentedTask(const Handle coroutine) : coroutine{ coroutine } {}

	~SegmentedTask()

	{

		if (coroutine) {

			coroutine.destroy();

		}

	}

	SegmentedTask(const SegmentedTask&) = delete;

	SegmentedTask& operator=(const SegmentedTask&) = delete;

	SegmentedTask(SegmentedTask&& other) noexcept : coroutine(other.coroutine) { other.coroutine = {}; }

	SegmentedTask& operator=(SegmentedTask&& other) noexcept

	{

		if (this != &other) {

			if (coroutine) {

				coroutine.destroy();

			}

			coroutine = other.coroutine;

			other.coroutine = {};

		}

		return *this;

	}

	void Resume() const { coroutine.resume(); }

	bool IsFinished() const { return coroutine.promise().returnValue.has_value(); }
	T GetReturnValue() const { return coroutine.promise().returnValue.value(); }
private:
	Handle coroutine;
};

int main()
{
    std::cout << "Hello World!\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
