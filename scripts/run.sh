accepted_build_types=("Release" "Debug")

if [ ! -z "$1" ]; then
    for acc in ${accepted_build_types[@]}; do
        if [[ $1 == $acc ]]; then
            ./build/$acc/main
        fi
    done
else
    echo "Build type not provided!"
fi
