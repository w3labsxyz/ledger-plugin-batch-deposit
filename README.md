[![Ensure compliance with Ledger guidelines](https://github.com/LedgerHQ/app-plugin-boilerplate/actions/workflows/guidelines_enforcer.yml/badge.svg?branch=develop)](https://github.com/LedgerHQ/app-plugin-boilerplate/actions/workflows/guidelines_enforcer.yml)
[![Compilation & tests](https://github.com/LedgerHQ/app-plugin-boilerplate/actions/workflows/build_and_functional_tests.yml/badge.svg?branch=develop)](https://github.com/LedgerHQ/app-plugin-boilerplate/actions/workflows/build_and_functional_tests.yml)

# Ledger Plugin for improved Ethereum staking experience

This repository contains the source code for a Ledger plugin that improves the Ethereum staking experience by interacting with our [Ethereum batch-deposit smart contract](https://www.github.com/w3labsxyz/ethereum-batch-deposit-contracts).
While our batch deposit smart contract can be used without this plugin, it helps with the user experience by providing a more user-friendly interface to signing the respective transactions. This is especially useful for larger deposits.

Technically speaking, this plugin is a lightweight application that interfaces with the native Ledger Ethereum application on Nano (S plus, X), Stax and Flex devices. It allows users to clear-sign interactions with the [Ethereum batch-deposit smart contract](https://www.github.com/w3labsxyz/ethereum-batch-deposit-contracts). It is designed to work hand-in-hand with the Ethereum application: When the Ethereum application detects our [Ethereum batch-deposit smart contract](https://www.github.com/w3labsxyz/ethereum-batch-deposit-contracts), it will call this plugin to query the elements to display and delegate extracting relevant information from the smart contract to the plugin.

## Development

We use a [justfile](https://github.com/casey/just) to wrap common development tasks. You can install `just` via `cargo`.

### Dependencies

This plugin requires the [Ethereum SDK](https://github.com/LedgerHQ/ethereum-plugin-sdk). We include it as a submodule in the `ethereum-plugin-sdk` directory. You can fetch it by running `just update-submodules`. Alternatively, you can clone the sdk manually and use the `ETHEREUM_PLUGIN_SDK` environment variable to point to the respective directory.

The rest of the build dependencies are managed by the [ledger-app-builder](https://github.com/LedgerHQ/ledger-app-builder). Run it with the following command:

```shell
# Linux
docker run --rm -ti --user "$(id -u):$(id -g)" --privileged -v "/dev/bus/usb:/dev/bus/usb" -v "$(realpath .):/app" ghcr.io/ledgerhq/ledger-app-builder/ledger-app-dev-tools:latest

# macOS
docker run  --rm -ti --user "$(id -u):$(id -g)" --privileged -v "$(pwd -P):/app" ghcr.io/ledgerhq/ledger-app-builder/ledger-app-dev-tools:latest

# Windows (with PowerShell)
docker run --rm -ti --privileged -v "$(Get-Location):/app" ghcr.io/ledgerhq/ledger-app-builder/ledger-app-dev-tools:latest
```

Inside of the container, you can choose which device to compile and load for by setting the `BOLOS_SDK` environment variable to the following values:

```shell
BOLOS_SDK=$NANOS_SDK
BOLOS_SDK=$NANOX_SDK
BOLOS_SDK=$NANOSP_SDK
BOLOS_SDK=$STAX_SDK
```

Followed by the respective command that you'd like to run:

```shell
make
make load
```

### Tests

To run our tests, we need to emulate the Ledger OS [BOLOS](https://developers.ledger.com/docs/device-app/architecture/bolos). Therefore we need [speculos](https://speculos.ledger.com/) among other dependencies for testing. Assuming you have Python3 setup and poetry installed, you can use a virtual env to install speculos:

```shell
python3 -m venv .venv
source .venv/bin/activate
poetry install
```

### Formatting

The C source code is formatted with [`clang-format`](https://clang.llvm.org/docs/ClangFormat.html). Apply the formatting using `just fmt`.

### Icons

https://developers.ledger.com/docs/device-app/deliver/deliverables/icons#device-icon

## Documentation

This plugin is documented in [PLUGIN_SPECIFICATON.md](https://github.com/w3labsxyz/ledger-plugin-batch-deposit/blob/main/PLUGIN_SPECIFICATION.md). The documentation entails:

- the smart contracts and functions supported by the plugin
