#include "virtual_memory_manager.hpp"
#include "logger.hpp"
#include <sstream>
#include <iomanip>

VirtualMemoryManager::VirtualMemoryManager() {
    // Constructor logic (if needed).
}

VirtualMemoryManager::~VirtualMemoryManager() {
    // Destructor cleanup (if needed).
}

bool VirtualMemoryManager::initialize() {
    Logger::getInstance().info("VirtualMemoryManager: Initialized virtual memory management.");
    return true;
}

bool VirtualMemoryManager::mapRegion(uint32_t virtualAddress, uint32_t physicalAddress, size_t size, MemoryPermissions permissions) {
    std::lock_guard<std::mutex> lock(pageTableMutex_);
    // Check if there is already a mapping for this region.
    if (pageTable_.find(virtualAddress) != pageTable_.end()) {
        Logger::getInstance().error("VirtualMemoryManager: Virtual address already mapped.");
        return false;
    }
    PageTableEntry entry { virtualAddress, physicalAddress, size, permissions };
    pageTable_[virtualAddress] = entry;
    Logger::getInstance().info("VirtualMemoryManager: Mapped virtual 0x" + std::to_string(virtualAddress) +
        " to physical 0x" + std::to_string(physicalAddress) +
        " (size: " + std::to_string(size) + " bytes, perms: " + std::to_string(static_cast<uint8_t>(permissions)) + ").");
    return true;
}

bool VirtualMemoryManager::unmapRegion(uint32_t virtualAddress) {
    std::lock_guard<std::mutex> lock(pageTableMutex_);
    auto it = pageTable_.find(virtualAddress);
    if (it == pageTable_.end()) {
        Logger::getInstance().error("VirtualMemoryManager: Attempt to unmap non-existent region.");
        return false;
    }
    pageTable_.erase(it);
    Logger::getInstance().info("VirtualMemoryManager: Unmapped region starting at virtual 0x" + std::to_string(virtualAddress));
    return true;
}

bool VirtualMemoryManager::translateAddress(uint32_t virtualAddress, uint32_t &physicalAddress) {
    std::lock_guard<std::mutex> lock(pageTableMutex_);
    // For simulation purposes, iterate over entries and see if the address falls within an entry.
    for (const auto &pair : pageTable_) {
        const PageTableEntry &entry = pair.second;
        if (virtualAddress >= entry.virtualAddress && virtualAddress < entry.virtualAddress + entry.size) {
            uint32_t offset = virtualAddress - entry.virtualAddress;
            physicalAddress = entry.physicalAddress + offset;
            Logger::getInstance().debug("VirtualMemoryManager: Translated virtual 0x" + 
                std::to_string(virtualAddress) + " to physical 0x" + std::to_string(physicalAddress));
            return true;
        }
    }
    Logger::getInstance().error("VirtualMemoryManager: Translation failed for virtual 0x" + std::to_string(virtualAddress));
    return false;
}

void VirtualMemoryManager::handlePageFault(uint32_t virtualAddress) {
    Logger::getInstance().error("VirtualMemoryManager: Page fault at virtual address 0x" + std::to_string(virtualAddress));
    // A production system might allocate a new page or notify the process manager.
}

std::string VirtualMemoryManager::dumpPageTable() {
    std::lock_guard<std::mutex> lock(pageTableMutex_);
    std::ostringstream oss;
    oss << "VirtualMemoryManager: Page Table Dump\n------------------------------------\n";
    for (const auto &pair : pageTable_) {
        const PageTableEntry &entry = pair.second;
        oss << "Virtual: 0x" << std::hex << entry.virtualAddress
            << " | Physical: 0x" << entry.physicalAddress
            << " | Size: " << std::dec << entry.size 
            << " | Perms: 0x" << std::hex << static_cast<int>(entry.permissions) << "\n";
    }
    return oss.str();
}
