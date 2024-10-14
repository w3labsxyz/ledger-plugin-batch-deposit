#include "plugin.h"

// EDIT THIS: Remove this function and write your own handlers!
static void handle_batch_deposit(ethPluginProvideParameter_t *msg, context_t *context) {
    if (context->go_to_offset) {
        if (msg->parameterOffset != context->offset + SELECTOR_SIZE) {
            return;
        }
        context->go_to_offset = false;
    }
    switch (context->next_param) {
        case WITHDRAWAL_ADDRESS:
            copy_address(context->withdrawal_address,
                         msg->parameter,
                         sizeof(context->withdrawal_address));
            context->next_param = PUBKEYS;
            break;
        case PUBKEYS:
            // story number of pubkeys in context
            context->number_of_validators = U4BE(msg->parameter, 0);
            context->next_param = SIGNATURES;
            break;
        case SIGNATURES:
            context->next_param = DEPOSIT_DATA_ROOTS;
            break;
        case DEPOSIT_DATA_ROOTS:
            context->next_param = UNEXPECTED_PARAMETER;
            break;
        // Keep this
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

void handle_provide_parameter(ethPluginProvideParameter_t *msg) {
    context_t *context = (context_t *) msg->pluginContext;
    // We use `%.*H`: it's a utility function to print bytes. You first give
    // the number of bytes you wish to print (in this case, `PARAMETER_LENGTH`) and then
    // the address (here `msg->parameter`).
    PRINTF("plugin provide parameter: offset %d\nBytes: %.*H\n",
           msg->parameterOffset,
           PARAMETER_LENGTH,
           msg->parameter);

    msg->result = ETH_PLUGIN_RESULT_OK;

    switch (context->selectorIndex) {
        case BATCH_DEPOSIT:
            handle_batch_deposit(msg, context);
            break;
        default:
            PRINTF("Selector Index not supported: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}
