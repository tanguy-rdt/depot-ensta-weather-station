const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>

<html>
    <style>
        .title {
            font-family: DelrosaHoliday;
            font-size: 30px;
            padding-top: 5em;

            text-align: center;
        }

        .content {
            padding-top: 2em;
            font-family: Coolvetica;
            font-size: 40px;
        }

        .typeData {
            float: left;
            height: 100%;
            width: 49%;

            text-align: right;
        }

        .data {
            float: right;
            height: 100%;
            width: 49%;

            text-align: left;
        }

        .footer-name{
            float: right;
            height: 100%;
            width: 10em;

            text-align: right;
            font-size: 20px;
        }

        .footer-logo-ensta{
            float: left;
            height: 100%;
            width: 20em;

            text-align: left;
        }

        .time{
	        text-align: center;
	        font-size: 20px;
	        padding-top: 25em;
	    }


        body {
            background-image:url('https://images.unsplash.com/photo-1556290160-d006087340ac?ixid=MnwxMTI1OHwwfDF8cmFuZG9tfHx8fHx8fHx8MTY1NzA0NTgxNQ&ixlib=rb-1.2.1&q=85&w=3600');
            background-repeat: no-repeat;
            background-size: cover; 
            background-color: black;

            color: White;
        }

        footer{
            width: 97%;
            position: absolute;
            bottom:0;
            padding-top:10em;
            padding-bottom: 1em;
            font-family: Coolvetica;
        }
    </style>

    <head>
        <meta charset="utf-8">
        <link rel="stylesheet" href="style.css" />
        <title>Weather station</title>
    </head>
    <body>
        <div class="title">
            <h1>Welcom on the weather station !</h1>
        </div>
        <div class="content">
            <div class="typeData">
                <p>Temperature indoor:</p>
                <p>Humidity indoor:</p>
                <p>Temperature outdoor:</p>
                <p>Humidity outdoor:</p>
                <p>Pressure:</p>
            </div>
            <div class="data"> 
                <p><span id="indoorTemp">0</span> °C</p>
                <p><span id="indoorRh">0</span> %</p>
                <p><span id="outdoorTemp">0</span> °C</p>
                <p><span id="outdoorRh">0</span> %</p>
                <p><span id="press">0</span> hPa</p>
            </div>
            <div class="time">
                <p><span id="day">0</span>/<span id="month">0</span>/<span id="year">0</span> <span id="hour">0</span>h<span id="min">0</span>m<span id="sec">0</span>s</p>
            </div>
        </div>
        <footer>
            <div class="footer-name">
                <p>Tanguy ROUDAUT</p>
                <p>Tom ALLAIN</p>
            </div>
            <div class="footer-logo-ensta">
                <img src="https://www.ensta-bretagne.fr/sites/default/files/2019-10/ensta-logoh-rvb-blanctransparent.png" width="300em">
            </div>
        </footer>
        <script>
            setInterval(function() {
                getIndoorTemp();
                getIndoorRh();
                getOutdoorTemp();
                getOutdoorRh();
                getPress();

                getDay();
                getMonth();
                getYear();
                getHour();
                getMin();
                getSec();
            }, 1000); //2000mSeconds update rate

            function getIndoorTemp() {
                var xhttp = new XMLHttpRequest();
                xhttp.onreadystatechange = function() {
                    if (this.readyState == 4 && this.status == 200) {
                        document.getElementById("indoorTemp").innerHTML = this.responseText;
                    }
                };
                xhttp.open("GET", "readIndoorTemp", true);
                xhttp.send();
            }

             function getIndoorRh() {
                var xhttp = new XMLHttpRequest();
                xhttp.onreadystatechange = function() {
                    if (this.readyState == 4 && this.status == 200) {
                        document.getElementById("indoorRh").innerHTML = this.responseText;
                    }
                };
                xhttp.open("GET", "readIndoorRh", true);
                xhttp.send();
            }

             function getOutdoorTemp() {
                var xhttp = new XMLHttpRequest();
                xhttp.onreadystatechange = function() {
                    if (this.readyState == 4 && this.status == 200) {
                        document.getElementById("outdoorTemp").innerHTML = this.responseText;
                    }
                };
                xhttp.open("GET", "readOutdoorTemp", true);
                xhttp.send();
            }

             function getOutdoorRh() {
                var xhttp = new XMLHttpRequest();
                xhttp.onreadystatechange = function() {
                    if (this.readyState == 4 && this.status == 200) {
                        document.getElementById("outdoorRh").innerHTML = this.responseText;
                    }
                };
                xhttp.open("GET", "readOutdoorRh", true);
                xhttp.send();
            }

             function getPress() {
                var xhttp = new XMLHttpRequest();
                xhttp.onreadystatechange = function() {
                    if (this.readyState == 4 && this.status == 200) {
                        document.getElementById("press").innerHTML = this.responseText;
                    }
                };
                xhttp.open("GET", "readPress", true);
                xhttp.send();
            }

            function getDay() {
                var xhttp = new XMLHttpRequest();
                xhttp.onreadystatechange = function() {
                    if (this.readyState == 4 && this.status == 200) {
                        document.getElementById("day").innerHTML = this.responseText;
                    }
                };
                xhttp.open("GET", "readDay", true);
                xhttp.send();
            }

            function getMonth() {
                var xhttp = new XMLHttpRequest();
                xhttp.onreadystatechange = function() {
                    if (this.readyState == 4 && this.status == 200) {
                        document.getElementById("month").innerHTML = this.responseText;
                    }
                };
                xhttp.open("GET", "readMonth", true);
                xhttp.send();
            }

            function getYear() {
                var xhttp = new XMLHttpRequest();
                xhttp.onreadystatechange = function() {
                    if (this.readyState == 4 && this.status == 200) {
                        document.getElementById("year").innerHTML = this.responseText;
                    }
                };
                xhttp.open("GET", "readYear", true);
                xhttp.send();
            }

            function getHour() {
                var xhttp = new XMLHttpRequest();
                xhttp.onreadystatechange = function() {
                    if (this.readyState == 4 && this.status == 200) {
                        document.getElementById("hour").innerHTML = this.responseText;
                    }
                };
                xhttp.open("GET", "readHour", true);
                xhttp.send();
            }

            function getMin() {
                var xhttp = new XMLHttpRequest();
                xhttp.onreadystatechange = function() {
                    if (this.readyState == 4 && this.status == 200) {
                        document.getElementById("min").innerHTML = this.responseText;
                    }
                };
                xhttp.open("GET", "readMin", true);
                xhttp.send();
            }

            function getSec() {
                var xhttp = new XMLHttpRequest();
                xhttp.onreadystatechange = function() {
                    if (this.readyState == 4 && this.status == 200) {
                        document.getElementById("sec").innerHTML = this.responseText;
                    }
                };
                xhttp.open("GET", "readSec", true);
                xhttp.send();
            }
        </script>
    </body>
</html>
)=====";