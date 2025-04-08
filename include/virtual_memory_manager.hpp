#ifndef VIRTUAL_MEMORY_MANAGER_HPP
#define VIRTUAL_MEMORY_MANAGER_HPP

#include <cstdint>
#include <cstddef>
#include <unordered_map>
#include <mutex>
#include <string>

// Define memory permissions as flags.
enum class MemoryPermissions : uint8_t {
    NONE    = 0,
    READ    = 1 << 0,
    WRITE   = 1 << 1,
    EXECUTE = 1 << 2
};

inline MemoryPermissions operator|(MemoryPermissions a, MemoryPermissions b) {
    return static_cast<MemoryPermissions>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

inline bool hasPermission(MemoryPermissions perms, MemoryPermissions flag) {
    return (static_cast<uint8_t>(perms) & static_cast<uint8_t>(flag)) != 0;
}

// Structure representing a simulated page table entry.
struct PageTableEntry {
    uint32_t virtualAddress;
    uint32_t physicalAddress;
    size_t size;                      // In bytes.
    MemoryPermissions permissions;
};

class VirtualMemoryManager {
public:
    VirtualMemoryManager();
    ~VirtualMemoryManager();

    // Initialize the virtual memory system.
    bool initialize();

    // Map a virtual address range to a physical address range with given permissions.
    bool mapRegion(uint32_t virtualAddress, uint32_t physicalAddress, size_t size, MemoryPermissions permissions);

    // Unmap a previously mapped virtual memory region.
    bool unmapRegion(uint32_t virtualAddress);

    // Translate a virtual address into a physical address.
    // Returns true and sets physicalAddress if mapping exists; otherwise returns false.
    bool translateAddress(uint32_t virtualAddress, uint32_t &physicalAddress);

    // Simulate handling a page fault.
    void handlePageFault(uint32_t virtualAddress);

    // Dump the current page table (for debug purposes).
    std::string dumpPageTable();

private:
    std::unordered_map<uint32_t, PageTableEntry> pageTable_;
    std::mutex pageTableMutex_;
};

#endif // VIRTUAL_MEMORY_MANAGER_HPP
