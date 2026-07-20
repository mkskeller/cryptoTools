#include <cryptoTools/Common/Defines.h>
#include <cryptoTools/Crypto/AES.h>
#include <random>
#include <sstream>
#include <iomanip>
#include <cstring>

namespace osuCrypto
{



    block PRF(const block& b, u64 i)
    {
        return AES(b).ecbEncBlock(toBlock(i));
    }

    void split(const std::string &s, char delim, std::vector<std::string> &elems) {
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            elems.push_back(item);
        }
    }

    std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> elems;
        split(s, delim, elems);
        return elems;
    }

    block sysRandomSeed()
    {
        std::random_device rd;
        auto ret = std::array<u32, 4>{rd(), rd(), rd(), rd()};
        block blk;
        memcpy(&blk, &ret, sizeof(block));
        return blk;
    }

    std::runtime_error maybe_runtime_error(const std::string& error)
    {
        std::cerr << error << std::endl;
//        std::terminate();
        return std::runtime_error(error);
    }
}
