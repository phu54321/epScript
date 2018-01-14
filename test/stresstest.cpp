#include <stdio.h>
#include <time.h>

extern "C" {
const char *compileString(
        const char *modname,
        const char *rawcode
);
void freeCompiledResult(const char *str);
};

auto source = ""
        "import piece;\n"
        "import tile;\n"
        "import selection as sel;\n"
        "import pieceRule.pawn;\n"
        "import pieceRule.knight;\n"
        "import pieceRule.bishop;\n"
        "import pieceRule.king;\n"
        "import pieceRule.queen;\n"
        "import pieceRule.rook;\n"
        "\n"
        "function onPluginStart() {\n"
        "    piece.placePiece(0, 0, $U(\"Rook\"),   $P7);\n"
        "    piece.placePiece(1, 0, $U(\"Knight\"), $P7);\n"
        "    piece.placePiece(2, 0, $U(\"Bishop\"), $P7);\n"
        "    piece.placePiece(3, 0, $U(\"King\"),   $P7);\n"
        "    piece.placePiece(4, 0, $U(\"Queen\"),  $P7);\n"
        "    piece.placePiece(5, 0, $U(\"Bishop\"), $P7);\n"
        "    piece.placePiece(6, 0, $U(\"Knight\"), $P7);\n"
        "    piece.placePiece(7, 0, $U(\"Rook\"),   $P7);\n"
        "    piece.placePiece(0, 1, $U(\"Pawn\"),   $P7);\n"
        "    piece.placePiece(1, 1, $U(\"Pawn\"),   $P7);\n"
        "    piece.placePiece(2, 1, $U(\"Pawn\"),   $P7);\n"
        "    piece.placePiece(3, 1, $U(\"Pawn\"),   $P7);\n"
        "    piece.placePiece(4, 1, $U(\"Pawn\"),   $P7);\n"
        "    piece.placePiece(5, 1, $U(\"Pawn\"),   $P7);\n"
        "    piece.placePiece(6, 1, $U(\"Pawn\"),   $P7);\n"
        "    piece.placePiece(7, 1, $U(\"Pawn\"),   $P7);\n"
        "    piece.placePiece(0, 7, $U(\"Rook\"),   $P8);\n"
        "    piece.placePiece(1, 7, $U(\"Knight\"), $P8);\n"
        "    piece.placePiece(2, 7, $U(\"Bishop\"), $P8);\n"
        "    piece.placePiece(3, 7, $U(\"King\"),   $P8);\n"
        "    piece.placePiece(4, 7, $U(\"Queen\"),  $P8);\n"
        "    piece.placePiece(5, 7, $U(\"Bishop\"), $P8);\n"
        "    piece.placePiece(6, 7, $U(\"Knight\"), $P8);\n"
        "    piece.placePiece(7, 7, $U(\"Rook\"),   $P8);\n"
        "    piece.placePiece(0, 6, $U(\"Pawn\"),   $P8);\n"
        "    piece.placePiece(1, 6, $U(\"Pawn\"),   $P8);\n"
        "    piece.placePiece(2, 6, $U(\"Pawn\"),   $P8);\n"
        "    piece.placePiece(3, 6, $U(\"Pawn\"),   $P8);\n"
        "    piece.placePiece(4, 6, $U(\"Pawn\"),   $P8);\n"
        "    piece.placePiece(5, 6, $U(\"Pawn\"),   $P8);\n"
        "    piece.placePiece(6, 6, $U(\"Pawn\"),   $P8);\n"
        "    piece.placePiece(7, 6, $U(\"Pawn\"),   $P8);\n"
        "}\n"
        "\n"
        "\n"
        "var beforeUnitPlayer, beforeUnitType;\n"
        "var beforeUnitX, beforeUnitY = -1, -1;\n"
        "\n"
        "function afterTriggerExec() {\n"
        "    const unitType, selX, selY = sel.getSelectedUnit();\n"
        "    if (unitType != -1) {\n"
        "        if(unitType == $U('Zerg Scourge')) {\n"
        "            piece.removePiece(selX, selY);\n"
        "            piece.placePiece(selX, selY, beforeUnitType, beforeUnitPlayer);\n"
        "            piece.removePiece(beforeUnitX, beforeUnitY);\n"
        "            RemoveUnit(\"Zerg Scourge\", Force3);\n"
        "\n"
        "            beforeUnitX = -1;\n"
        "            beforeUnitY = -1;\n"
        "        }\n"
        "        else if(beforeUnitX != selX || beforeUnitY != selY) {\n"
        "            const tileVal = tile.tile(selX, selY);\n"
        "            beforeUnitPlayer = tileVal / 1000;\n"
        "            beforeUnitType = tileVal % 1000;\n"
        "            beforeUnitX = selX;\n"
        "            beforeUnitY = selY;\n"
        "            RemoveUnit(\"Zerg Scourge\", Force3);\n"
        "\n"
        "            if (unitType == $U(\"Pawn\")) pawn.getPossibleDestination(beforeUnitPlayer, selX, selY);\n"
        "            else if(unitType == $U(\"Knight\")) knight.getPossibleDestination(beforeUnitPlayer, selX, selY);\n"
        "            else if(unitType == $U(\"Bishop\")) bishop.getPossibleDestination(beforeUnitPlayer, selX, selY);\n"
        "            else if(unitType == $U(\"King\")) king.getPossibleDestination(beforeUnitPlayer, selX, selY);\n"
        "            else if(unitType == $U(\"Queen\")) queen.getPossibleDestination(beforeUnitPlayer, selX, selY);\n"
        "            else if(unitType == $U(\"Rook\")) rook.getPossibleDestination(beforeUnitPlayer, selX, selY);\n"
        "        }\n"
        "    }\n"
        "    else {\n"
        "        RemoveUnit(\"Zerg Scourge\", Force3);\n"
        "    }\n"
        "    SetInvincibility(Enable, \"(any unit)\", AllPlayers, 'Anywhere');\n"
        "}";

int main(int argc, const char* argv[]) {
    int start = clock();
    printf("Compiling 1000 times - ");
    for(int i = 0 ; i < 1000 ; i++) {
        auto compiled = compileString("main", source);
        freeCompiledResult(compiled);
    }
    printf("%lums\n", clock() - start);
}
