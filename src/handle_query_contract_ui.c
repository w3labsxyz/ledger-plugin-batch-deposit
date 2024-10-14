#include "plugin.h"

static bool handle_batch_deposit_ui(ethQueryContractUI_t *msg, const context_t *context) {
    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, "Amount", msg->titleLength);

            const uint8_t *eth_amount = msg->pluginSharedRO->txContent->value.value;
            uint8_t eth_amount_size = msg->pluginSharedRO->txContent->value.length;

            // Converts the uint256 number located in `eth_amount` to its string representation and
            // copies this to `msg->msg`.
            return amountToString(eth_amount,
                                  eth_amount_size,
                                  WEI_TO_ETHER,
                                  "ETH",
                                  msg->msg,
                                  msg->msgLength);
        case 1:
            strlcpy(msg->title, "Number of Validators", msg->titleLength);

            return u64_to_string(context->number_of_validators, msg->msg, msg->msgLength);
        case 2:
            strlcpy(msg->title, "Withdrawal Address", msg->titleLength);

            // We need a random chainID for legacy reasons with `getEthAddressStringFromBinary`.
            // Setting it to `0` will make it work with every chainID :)
            uint64_t chainid = 0;

            // Get the string representation of the address stored in `context->withdrawal_address`.
            // Put it in `msg->msg`.
            return getEthDisplayableAddress(context->withdrawal_address,
                                            msg->msg,
                                            msg->msgLength,
                                            chainid);
        default:
            PRINTF("Received an invalid screenIndex\n");
    }

    return false;
}

void handle_query_contract_ui(ethQueryContractUI_t *msg) {
    context_t *context = (context_t *) msg->pluginContext;
    bool ret = false;

    // msg->title is the upper line displayed on the device.
    // msg->msg is the lower line displayed on the device.

    // Clean the display fields.
    memset(msg->title, 0, msg->titleLength);
    memset(msg->msg, 0, msg->msgLength);

    switch (context->selectorIndex) {
        case BATCH_DEPOSIT:
            ret = handle_batch_deposit_ui(msg, context);
            break;
        default:
            PRINTF("Selector index: %d not supported\n", context->selectorIndex);
    }

    msg->result = ret ? ETH_PLUGIN_RESULT_OK : ETH_PLUGIN_RESULT_ERROR;
}
