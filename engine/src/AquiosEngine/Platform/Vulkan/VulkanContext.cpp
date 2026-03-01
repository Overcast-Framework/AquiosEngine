#include "aqpch.h"
#include "VulkanContext.h"
#include "VKUtils.h"

#include <GLFW/glfw3.h>

void Aquios::Vulkan::VulkanContext::Init()
{
    vkb::InstanceBuilder builder;
    auto inst_ret = builder.set_app_name("AquiosEngine")
        .request_validation_layers()
        .use_default_debug_messenger()
        .require_api_version(1,3)
        .build();
    if (!inst_ret) { AQ_CORE_ERROR("[VK] Couldn't instantiate VkInstance"); }
    m_Instance = inst_ret.value();

    VkSurfaceKHR c_Surface;
    vk_check(glfwCreateWindowSurface(m_Instance.instance, m_WindowHandle, NULL, &c_Surface));

    m_Surface = c_Surface;

    VkPhysicalDeviceVulkan12Features enabledVk12Features{
    .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES,
    .descriptorIndexing = true,
    .shaderSampledImageArrayNonUniformIndexing = true,
    .descriptorBindingVariableDescriptorCount = true,
    .runtimeDescriptorArray = true,
    .bufferDeviceAddress = true
    };

    const VkPhysicalDeviceVulkan13Features enabledVk13Features{
    .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES,
    .pNext = &enabledVk12Features,
    .synchronization2 = true,
    .dynamicRendering = true,
    };

    const VkPhysicalDeviceFeatures enabledVk10Features{
    .samplerAnisotropy = VK_TRUE
    };

    vkb::PhysicalDeviceSelector selector{ m_Instance };
    m_PhysicalDevice = selector.set_surface(m_Surface)
        .set_minimum_version(1, 3)
        .require_dedicated_transfer_queue()
        .set_required_features_13(enabledVk13Features)
        .set_required_features(enabledVk10Features)
        .select()
        .value();
    if (!m_PhysicalDevice) { AQ_CORE_ERROR("[VK] Couldn't instantiate VkPhysicalDevice"); }

    vkb::DeviceBuilder device_builder{ m_PhysicalDevice };
    auto dev_ret = device_builder.build();
    if (!dev_ret) { AQ_CORE_ERROR("[VK] Couldn't instantiate VkDevice"); }
    m_Device = dev_ret.value();

    auto graphics_queue_ret = m_Device.get_queue(vkb::QueueType::graphics);
    if (!graphics_queue_ret) { AQ_CORE_ERROR("[VK] Couldn't get the graphics queue"); }
    m_GraphicsQueue = graphics_queue_ret.value();

    VmaVulkanFunctions vkFunctions{
    .vkGetInstanceProcAddr = vkGetInstanceProcAddr,
    .vkGetDeviceProcAddr = vkGetDeviceProcAddr,
    .vkCreateImage = vkCreateImage
    };
    VmaAllocatorCreateInfo allocatorCI{
        .flags = VMA_ALLOCATOR_CREATE_BUFFER_DEVICE_ADDRESS_BIT,
        .physicalDevice = m_PhysicalDevice,
        .device = m_Device,
        .pVulkanFunctions = &vkFunctions,
        .instance = m_Instance
    };

    vk_check(vmaCreateAllocator(&allocatorCI, &m_VMAllocator));
    vk_check(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_PhysicalDevice, m_Surface, m_SurfaceCaps));
}

void Aquios::Vulkan::VulkanContext::SwapBuffers()
{
}
