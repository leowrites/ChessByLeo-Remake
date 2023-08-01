//
// Created by Siqi Liu on 2023-07-31.
//

#pragma once


class CheckmateValidator {

    // take in the king position and the board
    // king is checkmate if
    // 1. king has nowhere to move
    // 2. (if is being checked vertically/horizontally/diagonally) no piece can move between
    // brute force:
    // 1. king would have 8 squares around it which it can move to, we can check all 8 to see if king can move
    //      validation: 8 * # of rooks * 8 +
    // 2. we can first figure out which direction king is being checked from, then we can go through all pieces
    //      if the piece can be placed in between the attacker and the king

};
