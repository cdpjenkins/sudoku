import io.kotest.matchers.shouldBe
import org.junit.jupiter.api.Test

class BoardTest {
    @Test
    fun `can parse and print a board`() {
        val board = Board.populate(BOARD1_INPUT)

        board.dumpToString() shouldBe BOARD1_INPUT
    }

    @Test
    fun `can set a single cell`() {
        val board = Board.populate(EMPTY_BOARD)

        board.setCell(Position(1, 1), 7)

        board.dumpToString() shouldBe EMPTY_BOARD_WITH_7_ADDED
    }
}

val EMPTY_BOARD = """
            _________
            _________
            _________
            _________
            _________
            _________
            _________
            _________
            _________
        """.trimIndent()

val EMPTY_BOARD_WITH_7_ADDED = """
            _________
            _7_______
            _________
            _________
            _________
            _________
            _________
            _________
            _________
        """.trimIndent()


val BOARD1_INPUT = """
            53__7____
            6__195___
            _98____6_
            8___6___3
            4__8_3__1
            7___2___6
            _6____28_
            ___419__5
            ____8__79
        """.trimIndent()
