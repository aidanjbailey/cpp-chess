#include "GameService.h"
#include "Board.h"
#include "ChessColour.h"
#include "GameState.h"
#include "MoveService.h"
#include "Turn.h"
#include "linear_search.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

chesspp::GameService::GameService(void)
    : to_play(chesspp::White), turn_counter(1), move_service(to_play, board),
      possible_move_list(move_service.GetAvailableTurns()), state(Ready){};

chesspp::ChessColour chesspp::GameService::GetToPlay(void) { return to_play; }

void chesspp::GameService::PrintBoard(void) {
  std::cout << board.toString() << std::endl;
}

chesspp::GameState chesspp::GameService::GetState(void) const { return state; }

void chesspp::GameService::Concede(void) { state = Gameover; }

std::vector<chesspp::Turn> chesspp::GameService::GetPossibleTurns() {
  return possible_move_list;
};

std::vector<std::pair<char, int>>
chesspp::GameService::GetMoveablePieces(void) {
  std::vector<std::pair<char, int>> result{
      {possible_move_list[0].From.first, possible_move_list[0].From.second}};
  for (auto source = possible_move_list.begin() + 1;
       source < possible_move_list.end(); source++) {
    if (result.back() == source->From)
      continue;
    result.emplace_back(source->From);
  }
  return result;
}

std::vector<std::pair<char, int>>
chesspp::GameService::GetPossibleMoves(std::pair<char, int> location) {
  std::vector<std::pair<char, int>> result;
  for (auto iter = possible_move_list.begin(); iter < possible_move_list.end();
       iter++)
    if (iter->From == location)
      result.emplace_back(iter->To);
  return result;
}

bool chesspp::GameService::PlayTurn(Turn turn) {
  if (search::linear_search(turn, &possible_move_list[0],
                            possible_move_list.size()) == -1)
    return false;

  board.MakeMove(turn.From, turn.To);
  turn_list.emplace_back(turn);
  turn_counter++;
  to_play = turn_counter % 2 == 0 ? Black : White;
  possible_move_list = move_service.GetAvailableTurns();
  return true;
}