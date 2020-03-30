document.getElementById("texten").innerHTML = "<p>Hello, Welcome to the 'No Snack Bowl's homepage.<br/></p>" 
+ "<p>What do you want to do?<br/><br/></p>" + "<p>Your results are:<br/></p>";

if (getQueryVarible("text") == "Tips") {
    document.getElementById("texten").innerHTML = "<p>There are many ways to stop snacking but sometimes you need some help, so here are some tips to help you stop.<br/></p>"+
    "<h2>EAT PROPER MEALS<br/></h2>" + "<p>If you want to snack less it is really important that you eat enough. If you don’t eat enough to fill yourself, the cravings for snacks will keep coming. Make sure you eat the fats and carbs your body requires to function properly. This is different for everybody. People with a more active lifestyle will require more food than people with a passive lifestyle and a sitting job.<br/<</p>"
    + "<h2>SPREAD YOUR MEALS OVER THE DAY<br/></h2>" + "<p>It is better to have multiple eating moments during the day in which you eat a bit less, than just two or three moments in which you eat a lot. This will help you control your blood sugar and avoid big peaks and lows. The peaks and lows in your blood sugar are the main reason you feel like snacking. It will also keep your metabolism active all day.<br/></p>"
    + "<h2>PLAN WHEN YOU EAT<br/></h2>" + "<p>Create a plan for yourself: when do you eat what. Prepare your snacks so you have decent portions and temptations to get more will be smaller. When you have your snacks planned in advance you’re way more likely to eat only that and you have something to look forward to.<br/></p>"
    + "<h2>DRINK WATER, LOTS OF IT<br/></h2>" + "<p>Often when you think you’re hungry and go looking for a snack, you’re actually just thirsty. Drink a glass of water, wait for 15 minutes and ask yourself if you still want to get that snack. Chances are that your cravings are gone.<br/></p>"
    + "<h2>REPLACE CANDY FOR FRUIT<br/></h2>" + "<p>Whenever you do crave something sweet and can’t stop yourself, replace your candy by something healthier. Take a few grapes, an apple or a banana. This will get your blood sugar up again. You can also choose something that contains some healthy fats like half an avocado or a handful cashews.<br/></p>"
    + "<h2>ASK YOURSELF: AM I ACTUALLY HUNGRY OR JUST BORED?<br/></h2>" + "<p>We have a tendency to start snacking when we are not doing anything else. Ask yourself this question and give a honest reply. If you’re just bored: distract yourself.<br/></p>"
    + "<h2>DISTRACT YOURSELF<br/></h2>" + "<p>Whenever you feel the urge to take a snack, go do something else. Go for a walk, clean your kitchen, start reading a book, anything. But whenever you distract yourself from your cravings, they are most likely to go away.<br/></p>"
    + "<h2>MEASURE WHAT YOU EAT<br/></h2>" + "<p>It is proven that whenever you keep track of the amount of calories you eat on a day, you eat less. This is mainly because it makes you very conscious of what you eat. It can also be confronting to see how much you’ve already eaten. So keep a diary and write down everything you eat and drink.<br/></p>"
    + "<h2>PUT YOUR SNACKS OUT OF REACH<br/></h2>" + "<p>Whenever your snacks are within reach, you will more easily grab them. Make sure you put yours out of reach and don't open snacks bags. Research shows that if you have to open a bag or box to get to your snack, you will less likely go back for it, because it requires a more conscious action.<br/></p>"
    + "<h2>DON’T COMPLETELY DENY YOURSELF ANYTHING<br/></h2>" + "<p>Treat yourself every once in a while. If you really love chocolate reward yourself with a little piece every once in a while. This way you have something to look forward to. If you completely deny yourself something, chances are that at some point you will crack and eat the whole chocolate bar. So don’t completely deny yourself anything, but simply limit it.<br/></p>"
    + "<h2>DON'T LOSE HOPE<br/></h2>" + "<p>It may be hard and you wont get there imidiatly, but keep trying and follow these tips and you will sooner or later stop snacking. You can't master a new skill in a day and you can't change your habits in 15 minutes, but if you keep trying you will get there.<br/></p>";
}

if (getQueryVarible("text") == "Result") {
    document.getElementById("texten").innerHTML = "<p>This page will explain what your results mean, and what all the other results mean.<br/></p>"
    + "<h2>Movment 0 - 5 and Close 0 - 3<br/></h2>" + "<p>You have done very well, you did not try to take snacks or you only tried a few times, keep it up!<br/></p>"
    + "<h2>Movment 6 - 10 and Close 4 - 6<br/></h2>" + "<p>You need to keep trying, you did well but you still have some ways to go. Look at the tips and you will soon get better at not taking snacks.<br/></p>"
    + "<h2>Movment 11 - 14 and Close 7 - 9<br/></h2>" + "<p>You need to keep trying, you did not do so well and have to work a bit more. Look at the tips and you will soon get better at not taking snacks.<br/></p>"
    + "<h2>Movment 15 and/or Close 10<br/></h2>" + "<p>You need to keep trying, you did not do well. You tried too many times to take snacks and now the bowl is closed so you can't even try to take any more snacks. You should look at the tips so you can do better next time. And remember even if you did not do well this time next time you know more and can do better.<br/></p>";
}

if (getQueryVarible("text") == "Home") {
    document.getElementById("texten").innerHTML = "<p>Hello, Welcome to the 'No Snack Bowl's homepage.<br/></p>"
    + "<p>What do you want to do?<br/><br/></p>" + "<p>Your results are:<br/></p>";
}

function getQueryVarible(variable){
    var query = window.location.search.substring(1);
    var vars = query.split("&");
    for (var i=0;i<vars.length;i++) {
            var pair = vars[i].split("=");
            if(pair[0] == variable){return pair[1];}
    }
    return(false);
}