//
// Created by Siqi Liu on 2023-07-28.
//

#pragma once

#include <iostream>
#include <string>

namespace Chess
{
    inline std::string GetAssetPath(const std::string& assetName)
    {
        std::cout << ASSETS_PATH + assetName <<std::endl;
        return ASSETS_PATH + assetName;
    }
    using namespace std;
    const std::string whitePawnUnselected { GetAssetPath("whitePawnIcon.png")};
    const std::string whitePawnSelected { GetAssetPath("whitePawnSelected.png")};
    const std::string blackPawnUnselected { GetAssetPath("blackPawnIcon.png")};
    const std::string blackPawnSelected { GetAssetPath("blackPawnSelected.png")};

    const std::string whiteRookUnselected { GetAssetPath("whiteRookIcon.png")};
    const std::string whiteRookSelected { GetAssetPath("whiteRookSelected.png")};
    const std::string blackRookUnselected { GetAssetPath("blackRookIcon.png")};
    const std::string blackRookSelected { GetAssetPath("blackRookSelected.png")};

    const std::string whiteKnightUnselected { GetAssetPath("whiteKnightIcon.png")};
    const std::string whiteKnightSelected { GetAssetPath("whiteKnightSelected.png")};
    const std::string blackKnightUnselected { GetAssetPath("blackKnightIcon.png")};
    const std::string blackKnightSelected { GetAssetPath("blackKnightSelected.png")};

    const std::string whiteBishopUnselected { GetAssetPath("whiteBishopIcon.png")};
    const std::string whiteBishopSelected { GetAssetPath("whiteBishopSelected.png")};
    const std::string blackBishopUnselected { GetAssetPath("blackBishopIcon.png")};
    const std::string blackBishopSelected { GetAssetPath("blackBishopSelected.png")};

    const std::string whiteQueenUnselected { GetAssetPath("whiteQueenIcon.png")};
    const std::string whiteQueenSelected { GetAssetPath("whiteQueenSelected.png")};
    const std::string blackQueenUnselected { GetAssetPath("blackQueenIcon.png")};
    const std::string blackQueenSelected { GetAssetPath("blackQueenSelected.png")};

    const std::string whiteKingUnselected { GetAssetPath("whiteKingIcon.png")};
    const std::string whiteKingSelected { GetAssetPath("whiteKingSelected.png")};
    const std::string whiteKingInCheck { GetAssetPath("whiteKingInCheck.png")};
    const std::string blackKingUnselected { GetAssetPath("blackKingIcon.png")};
    const std::string blackKingSelected { GetAssetPath("blackKingSelected.png")};
    const std::string blackKingInCheck { GetAssetPath("blackKingInCheck.png")};
}
