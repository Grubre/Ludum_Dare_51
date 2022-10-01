build_types=()
accepted_build_types=("Release" "Debug")

for arg in "$@"; do
    for acc in ${accepted_build_types[@]}; do
        if [[ $arg == $acc ]]; then
            build_types+=($arg)
        fi
    done
done

for build_type in ${build_types[@]}; do
    echo "Generating ${build_type} configuration..."
    cmake -S . -B build/$build_type -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=$build_type
    cmake --build build/$build_type
    if test -f "compile_commands.json"; then
        rm compile_commands.json
    fi
    ln -s build/${build_type}/compile_commands.json compile_commands.json
done
