default:
    just --list

update-submodules:
    git submodule update --init --recursive

fmt:
    clang-format -i src/*.c src/*.h

convert:
    convert nanos_app_<token>.gif -crop 14x14+1+1 +repage -negate nanox_app_<token>.gif

build:
    # Build the plugin for Nano S
    docker run --rm -ti  -v "$(realpath .):/app" --privileged -v "/dev/bus/usb:/dev/bus/usb" --user $(id -u $USER):$(id -g $USER) ghcr.io/ledgerhq/ledger-app-builder/ledger-app-builder:latest sh -c 'BOLOS_SDK=$NANOS_SDK make'
    # Build the ethereum-app for Nano S
    docker run --rm -ti  -v "$(realpath ./tests/.test_dependencies/ethereum):/app" --privileged -v "/dev/bus/usb:/dev/bus/usb" --user $(id -u $USER):$(id -g $USER) ghcr.io/ledgerhq/ledger-app-builder/ledger-app-builder:latest sh -c 'BOLOS_SDK=$NANOS_SDK CAL_TEST_KEY=1 DOMAIN_NAME_TEST_KEY=1 SET_PLUGIN_TEST_KEY=1 NFT_TEST_KEY=1 make'
    # Build the plugin for Nano X
    # Build the plugin for Nano SP
    # Build the plugin for Stax
    # Build the plugin for Flex

test:
    # pytest -v tests/ --device all
    pytest -v tests/ --device nanos

run-speculos device:
    docker run --rm -it \
      --user $(id -u):$(id -g) \
      -v "$(realpath .)/build:/speculos/plugin" \
      -v "$(realpath ./tests/.test_dependencies/ethereum)/build:/speculos/app" \
      -v "/tmp/.X11-unix:/tmp/.X11-unix" \
      -e DISPLAY="host.docker.internal:0" \
      --publish 41000:41000 \
      --publish 5001:5001 \
      ghcr.io/ledgerhq/ledger-app-builder/ledger-app-dev-tools:latest \
      speculos \
        --display headless \
        --vnc-port 41000 \
        --api-port 5001 \
        -l /speculos/plugin/{{ device }}/bin/app.elf \
        --model {{ device }} \
        /speculos/app/{{ device }}/bin/app.elf
