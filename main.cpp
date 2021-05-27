#include <iostream>
#include "v8.h"
#include "libplatform/libplatform.h"
int main(int args, char** argv) {
    // 初始化v8国际化
    v8::V8::InitializeICUDefaultLocation(argv[0]);
    // 初始化v8快照，教程下面会详细说明
    v8::V8::InitializeExternalStartupData(argv[0]);
    // 构建v8运平台，这里我们使用了默认的平台，这里面只要是怎样调度任务，线程池的启动线程等。后面内容会简介
    std::unique_ptr<v8::Platform> platform = v8::platform::NewDefaultPlatform();
    // 执行平台的初始化。创建v8的线程池等工作
    v8::V8::InitializePlatform(platform.get());
    v8::V8::Initialize();
    // 创建隔离实例
    v8::Isolate::CreateParams create_params;
    create_params.array_buffer_allocator = v8::ArrayBuffer::Allocator::NewDefaultAllocator();
    // 创建句柄作用域，下面内容会介绍为何需要创建句柄作用域
    v8::Isolate* isolate = v8::Isolate::New(create_params);
    {
        // 创建隔离实例作用域，下面会详细介绍为何需要隔离实例作用域
        v8::Isolate::Scope isolate_scope(isolate);
        v8::HandleScope handle_scope(isolate);
        // 创建执行上下文，函数的调用，js代码的编译和函数的执行都需要绑定执行上下文，下面章节会介绍
        v8::Local<v8::Context> context = v8::Context::New(isolate);
        // 执行上下文作用域，下面会
        v8::Context::Scope context_scope(context);
        // 创建js脚本源码。正常是通过网络流或者文件去获取js文件，然后转换成  v8::Local<v8::String>数据类型。这里为了简单展示
        v8::Local<v8::String> source = v8::String::NewFromUtf8Literal(isolate, "'Hello' + ', World!'");
        // 编译源代码
        v8::Local<v8::Script> script =
                v8::Script::Compile(context, source).ToLocalChecked();
        // 执行脚本
        v8::Local<v8::Value> result = script->Run(context).ToLocalChecked();
        // 转换数据，通过打印结构
        v8::String::Utf8Value utf8(isolate, result);
        std::cout << *utf8 << std::endl;
    }
    // 销毁隔离实例
    isolate->Dispose();
    // 销毁v8引擎
    v8::V8::Dispose();
    // 关闭v8平台
    v8::V8::ShutdownPlatform();
    delete create_params.array_buffer_allocator;
    return 0;
}
