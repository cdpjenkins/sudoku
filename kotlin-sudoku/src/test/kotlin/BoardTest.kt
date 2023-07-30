import io.kotest.matchers.shouldBe
import org.junit.jupiter.api.Test

class BoardTest {
    @Test
    fun `can parse and print a board`() {
        val board = Board.parse(BOARD1_INPUT)

        board.dumpToString() shouldBe BOARD1_INPUT
    }

    @Test
    fun `can set a single cell`() {
        val board = Board.populate(EMPTY_BOARD)

        board.setCell(Position(1, 1), 7)

        board.dumpToString() shouldBe EMPTY_BOARD_WITH_7_ADDED
    }

    @Test
    fun `can solve a row`() {
        val board = Board.populate(
            """
                12345678_
                _________
                _________
                _________
                _________
                _________
                _________
                _________
                _________
            """.trimIndent()
        )

        board.dumpToString() shouldBe """
                123456789
                _________
                _________
                _________
                _________
                _________
                _________
                _________
                _________
            """.trimIndent()
    }

    @Test
    fun `can solve a column`() {
        val board = Board.populate(
            """
                ________1
                ________2
                ________3
                ________4
                ________5
                ________6
                ________7
                ________8
                _________
            """.trimIndent()
        )

        board.dumpToString() shouldBe """
                ________1
                ________2
                ________3
                ________4
                ________5
                ________6
                ________7
                ________8
                ________9
            """.trimIndent()
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
