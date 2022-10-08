// restart the game
var restart = document.querySelector("#b");


//grabs all the squares
var squares = document.querySelectorAll("td");

//clear all square on board
function clearBoard() {
    for(var i = 0; i < squares.length; i++){
        squares[i].textContent = '';
    }
}

restart.addEventListener('click', clearBoard);
//input a square
function changeMarker() {
    if (this.textContent === ''){
        this.textContent = 'X';
    } else if (this.textContent === 'X'){
        this.textContent = 'O';
    } else {
        this.textContent = '';
    }
}

for (var i = 0; i < squares.length; i++){
    squares[i].addEventListener('click', changeMarker);
}

//output a square


//check if winner





//check square marker


// for loop to add event listener to all squares
