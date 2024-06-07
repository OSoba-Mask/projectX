
let redButton = document.querySelector("#red-btn");
let jokeButton = document.querySelector("#joke-btn");

jokeButton.addEventListener("click", function() {
    alert("It works");
    
    fetch('https://official-joke-api.appspot.com/random_joke')
    .then((response) => {return response.json();})
    .then((data) => {alert(data.setup, data.punchline); });
});

redButton.addEventListener("click", function() {
    console.log("YOU DARE TO CLICK ME!");
    document.body.style.background = "#000";
});

