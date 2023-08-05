//
// Created by Siqi Liu on 2023-07-31.
//

#pragma once

#include "utility/utility.h"
#include "entity/board/Board.h"
#include "utility/check_validator/CheckValidator.h"

namespace Chess {
    bool IsCheckmate(const std::shared_ptr<Piece>& king, Board &board);
}
