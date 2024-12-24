#include <iostream>
#include <PKF.h>

int main()
{
    auto keyFormat = std::make_shared<PKF::KeyFormat>();

    std::cout << keyFormat->m_segmentLength << std::endl;
    std::cout << keyFormat->m_segmentCount << std::endl;
    std::cout << keyFormat->m_hasCheckSum << std::endl;
    std::cout << keyFormat->m_separator << std::endl;

    std::shared_ptr<PKF::KeyFormat> keyF = nullptr;

    //PKF::ProductKeyGenerator keyGenerator(keyF);

    std::cout << "------------------------------------------" << std::endl;

    return 0;
}