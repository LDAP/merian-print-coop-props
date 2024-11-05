#include "merian/vk/context.hpp"

int main() {
    spdlog::set_level(spdlog::level::err);

    const merian::ContextCreateInfo context_create_info{
        .application_name = "merian-print-coop-props",
    };
    const merian::ContextHandle context = merian::Context::create(context_create_info);

    if (!context->get_physical_device()->extension_supported(
            VK_KHR_COOPERATIVE_MATRIX_EXTENSION_NAME)) {
        SPDLOG_ERROR("{} not supported", VK_KHR_COOPERATIVE_MATRIX_EXTENSION_NAME);
    }

    fmt::println("Supported shapes for Result = A * B + C with");
    fmt::println("- M is the number of rows in matrices A, C, and Result");
    fmt::println("- K is the number of columns in matrix A and rows in matrix B");
    fmt::println("- N is the number of columns in matrices B, C, Result");
    fmt::println("\n");

    for (const auto props : context->get_physical_device()->get_cooperative_matrix_properties()) {
        fmt::println("M x K x N = {} x {} x {}", props.MSize, props.KSize, props.NSize);
        fmt::println("A type = {}, B type = {}, C type = {}, Result type = {}",
                   vk::to_string(props.AType), vk::to_string(props.BType),
                   vk::to_string(props.CType), vk::to_string(props.ResultType));
        fmt::println("Saturating accumulation must be present: {}",
                   bool(props.saturatingAccumulation));
        fmt::println("Scope: {}", vk::to_string(props.scope));
        fmt::println("");
    }

    return 0;
}
