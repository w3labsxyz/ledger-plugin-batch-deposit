# Technical Specification

## About

This plugin is a convenience wrapper for the smart contracts of w3.labs.

## Smart Contracts

The smart contracts covered by the plugin are the following:

| Network | Version | Smart Contract | Address                                      |
| ------- | ------- | -------------- | -------------------------------------------- |
| Mainnet | V1      | BatchDeposit   | `0x8fC32441C13706bB981A506FdE65DeDD5dEF3981` |
| Holesky | V1      | BatchDeposit   | `0xf079e540F598a85C22dA6eb570236B2169bE4962` |

## Functions

The functions exposed by the smart contracts above that are covered by this plugin are:

| Contract     | Function     | Selector     | Displayed Parameters                                                                     |
| ------------ | ------------ | ------------ | ---------------------------------------------------------------------------------------- |
| BatchDeposit | batchDeposit | `0xedc06875` | <table><tbody> <tr><td><code>address withdrawalAddress</code></td></tr> </tbody></table> |
