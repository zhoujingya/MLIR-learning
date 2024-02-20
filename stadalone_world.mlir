func.func @main() {
    // CHECK: %{{.*}} = call i32 (ptr, ...) @printf(ptr @hello_word_string)
    "standalone.world"() : () -> ()
    return
}