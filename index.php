<?php

session_start();
$servername = "localhost";
$username = "root";
$password = "";
$db = "restau";
$conn = null;
try {
	$conn = new PDO("mysql:host=$servername;dbname=$db", $username, $password);
	$conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
	//echo "Connected successfully <br/>";
} catch (PDOException $e) {
	echo "Connection failed: " . $e->getMessage();
}


try {
	$req = "SELECT * FROM tawla";
	$statement = $conn->query($req);
	$rows = "";
} catch (PDOException $e) {
	die($e->getMessage());
}


$rows = $rows;
?>6
<!DOCTYPE html>
<html>

<head>

	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<title>Welcome to Oishī Meals...</title>
	<link rel="stylesheet" type="text/css" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0/css/all.min.css">

	<!-- custom css file link -->
	<link rel="stylesheet" type="text/css" href="assets/style/stylish.css">

	<!-- Link Swiper's CSS -->
	<link rel="stylesheet" href="https://unpkg.com/swiper/swiper-bundle.min.css">
	<link rel="shortcut icon" type="x-icon" href="assets/images/logo.png">
</head>

<body>
	<!-- header section start -->
	<header>
		<a href="#" class="logo"><img src="assets/images/logo.png"></a>

		<nav class="navbar">
			<a href="#home" class="active">home</a>
			<a href="#about">about</a>
			<a href="#menu">menu</a>
			<a href="#team">team</a>
			<a href="#reservation">reservation</a>
			<a href="#blog">blog</a>

		</nav>


		<div class="icons">
			<i class="fas fa-bars" id="menu"></i>
			<i class="fas fa-search"></i>
			<i class="fas fa-heart"></i>
			<i class="fas fa-shopping-cart"></i>
			<a href="view/signin.php"><i class="fas fa-sign-in"></i> </a>

		</div>
	</header>
	<!-- header section end -->

	<!-- slider section start -->
	<div class="home" id="home">
		<div class="swiper home-slider">
			<div class="swiper-wrapper wrapper">
				<div class="swiper-slide slide slide1">
					<div class="content">
						<img src="assets/images/crown-symbol.png">

						<h3> Oishī meals</h3>
						<h1>delicious meals</h1>
						<p>
							give away your beloved customers
						</p>
						<a href="#" class="btn">order now</a>
					</div>
				</div>

				<div class="swiper-slide slide slide2">
					<div class="content">
						<img src="assets/images/crown-symbol.png">

						<h3>sale of 10% this dish</h3>
						<h1>the fresh</h1>
						<p>
							food restaurant
						</p>
						<a href="#" class="btn">order now</a>
					</div>
				</div>

				<div class="swiper-slide slide slide3">
					<div class="content">
						<img src="assets/images/crown-symbol.png">

						<h3>we are open</h3>
						<h1>fresh fruits</h1>
						<p>
							you will love it
						</p>
						<a href="#" class="btn">order now</a>
					</div>
				</div>
			</div>

			<div class="swiper-pagination"></div>

		</div>
	</div>
	<!-- slider section ends -->

	<!-- welcome section start -->
	<section class="welcome" id="about">
		<h1 class="heading">WELCOME TO Oishī meals</h1>
		<center>
			<h3 class="sub-heading"> Luxury & Quality </h3>
		</center>

		<div class="box-container">
			<div class="box">
				<div class="image">
					<img src="assets/images/post-thumb-1.jpg">
				</div>

				<div class="content">
					<h3>PROFESSIONAL LEVEL</h3>
					<p>nor again is there anyone who loves or pursues or desires to obtain pain of itself, becuase it is pain, but because occasionally circumstances occur.</p>

					<a href="#" class="btn">Read More</a>
				</div>
			</div>

			<div class="box">
				<div class="image">
					<img src="assets/images/post-thumb-2.jpg">
				</div>

				<div class="content">
					<h3>FOR THE KIDS</h3>
					<p>Cute Bears Onigiri For Kids And More To Make Your Child Smile.</p>

					<a href="#" class="btn">Read More</a>
				</div>
			</div>

			<div class="box">
				<div class="image">
					<img src="assets/images/post-thumb-3.jpg">
				</div>

				<div class="content">
					<h3>DELICIOUS DESSERTS</h3>
					<p>Delicous Wagashi For Dessert Lovers.</p>

					<a href="#" class="btn">Read More</a>
				</div>
			</div>
		</div>
	</section>
	<!-- welcome section start -->

	<!-- our menu section start -->
	<section class="our-menu" id="menu">
		<h1 class="heading">our food menu</h1>
		<center>
			<h3 class="sub-heading"> see what we offer </h3>
		</center>

		<div class="menu-container">

			<div class="item">
				<div class="item-name">
					<h2>Main Course</h2>
					<!--	<img src="assets/images/drinks.png">-->
				</div>

				<div class="item-body">
					<div class="item-menu">
						<h3>Oyadokon (japenese Chicken And Egg Rice Bowl)</h3>
						<span class="dots"></span>
						<h3>$40</h3>

						<ul>
							<li><a href="#">oishi</a></li>
							<li><a href="#">japenese</a></li>
							<li><a href="#">Sausage</a></li>

						</ul>
					</div>

					<div class="item-menu">
						<h3>Cream Cheese and Crab Sushi Rolls</h3>
						<span class="dots"></span>
						<h3>$35</h3>

						<ul>
							<li><a href="#">Mushrooms</a></li>
							<li><a href="#">japenese</a></li>
							<li><a href="#">Sausage</a></li>

						</ul>
					</div>

				</div>
			</div>

			<div class="item">
				<div class="item-name">
					<h2>Soups & salads</h2>
					<img src="assets/images/soups-and-salads.png">
				</div>

				<div class="item-body">
					<div class="item-menu">
						<h3>Nabeyaki Udon</h3>
						<span class="dots"></span>
						<h3>$40</h3>

						<ul>
							<li><a href="#">oishi</a></li>
							<li><a href="#">japenese</a></li>
							<li><a href="#">Sausage</a></li>

						</ul>
					</div>

					<div class="item-menu">
						<h3>Kiriboshi Daikon</h3>
						<span class="dots"></span>
						<h3>$26</h3>

						<ul>
							<li><a href="#">Mushrooms</a></li>
							<li><a href="#">japense</a></li>
							<li><a href="#">Sausage</a></li>

						</ul>
					</div>

				</div>
			</div>


			<div class="item">
				<div class="item-name">
					<h2>Drinks</h2>
					<img src="assets/images/drinks.png">
				</div>

				<div class="item-body">
					<div class="item-menu">
						<h3>Royal Milk Tea</h3>
						<span class="dots"></span>
						<h3>$40</h3>

						<ul>
							<li><a href="#">oishi</a></li>
							<li><a href="#">japenese</a></li>
							<li><a href="#">Sausage</a></li>

						</ul>
					</div>

					<div class="item-menu">
						<h3>Green Tea</h3>
						<span class="dots"></span>
						<h3>$26</h3>

						<ul>
							<li><a href="#">Mushrooms</a></li>
							<li><a href="#">japenese</a></li>
							<li><a href="#">Sausage</a></li>

						</ul>
					</div>

				</div>
			</div>


			<div class="item">
				<div class="item-name">
					<h2>Desserts</h2>
					<img src="assets/images/desserts.png">
				</div>

				<div class="item-body">
					<div class="item-menu">
						<h3>Frutu Sando (Fruit Sandwich)</h3>
						<span class="dots"></span>
						<h3>$40</h3>

						<ul>
							<li><a href="#">oishi</a></li>
							<li><a href="#">japenese</a></li>
							<li><a href="#">Sausage</a></li>

						</ul>
					</div>

					<div class="item-menu">
						<h3>Castella</h3>
						<span class="dots"></span>
						<h3>$26</h3>

						<ul>
							<li><a href="#">Mushrooms</a></li>
							<li><a href="#">japenese</a></li>
							<li><a href="#">Sausage</a></li>

						</ul>
					</div>

				</div>
			</div>

		</div>
	</section>
	<!-- our menu section ends -->

	<!-- our team section start -->
	<section class="our-team" id="team">
		<h1 class="heading">our talented chef</h1>
		<center>
			<h3 class="sub-heading"> Experience & Enthusiasm </h3>
		</center>

		<div class="our-chef">
			<div class="item">
				<div class="image">
					<img src="assets/images/our-chef-1.jpg">
				</div>

				<div class="chef-info">
					<div>
						<h3>Jerry robertson</h3>
						<span>master chef</span>

						<ul>
							<li><a href="#"><i class="fa-brands fa-instagram"></i></a></li>
							<li><a href="#"><i class="fa-brands fa-twitter"></i></a></li>
							<li><a href="#"><i class="fa-brands fa-whatsapp"></i></a></li>
							<li><a href="#"><i class="fa-brands fa-linkedin-in"></i></a></li>
						</ul>
					</div>
				</div>
			</div>

			<div class="item">
				<div class="image">
					<img src="assets/images/our-chef-2.jpg">
				</div>

				<div class="chef-info">
					<div>
						<h3>Corol rowson</h3>
						<span>master chef</span>

						<ul>
							<li><a href="#"><i class="fa-brands fa-instagram"></i></a></li>
							<li><a href="#"><i class="fa-brands fa-twitter"></i></a></li>
							<li><a href="#"><i class="fa-brands fa-whatsapp"></i></a></li>
							<li><a href="#"><i class="fa-brands fa-linkedin-in"></i></a></li>
						</ul>
					</div>
				</div>
			</div>

			<div class="item">
				<div class="image">
					<img src="assets/images/our-chef-3.jpg">
				</div>

				<div class="chef-info">
					<div>
						<h3>taylor mccoy</h3>
						<span>master chef</span>

						<ul>
							<li><a href="#"><i class="fa-brands fa-instagram"></i></a></li>
							<li><a href="#"><i class="fa-brands fa-twitter"></i></a></li>
							<li><a href="#"><i class="fa-brands fa-whatsapp"></i></a></li>
							<li><a href="#"><i class="fa-brands fa-linkedin-in"></i></a></li>
						</ul>
					</div>
				</div>
			</div>


		</div>
	</section>
	<!-- our team section ends -->


	<!-- reservation section start -->
	<div class="reservation" id="reservation">
		<div class="image">

		</div>

		<div class="form">
			<h1 class="heading">book a table</h1>
			<center>
				<h3 class="sub-heading">~ check out our place ~ </h3>
			</center>

			<form method="POST" action="./add.php" onsubmit="return checkInputs()">
				<div class="form-holder">

					<div>
						<input type="text" name="first_name" id="first_name" placeholder="Name">
						<input type="text" name="last_name" id="last_name" placeholder="Last Name">
						<input type="email" name="email" id="email" placeholder="Email">
					</div>
					<!--<div>
						<div class="form-groupe mb-3">
							<label style="color:white">Gender:</label> &nbsp;
							<input type="radio" class="form-check-input" name="gender" id="male" value="male">
							<label for="male" class="form-input-label" style="color:white">Male</label>
							&nbsp;
							<input type="radio" class="form-check-input" name="gender" id="female" value="female">
							<label for="female" class="form-input-label" style="color:white">Female</label>
						</div>
					</div>-->
					<div>
						<input type="text" name="phone" id="phone" placeholder="Your Phone Number" required>
						<select name="table">


							<option value="">Select a table </option>

							<?php
							while ($row = $statement->fetch()) {

								if ($row["STATUS"] == 0) {
									echo "<option value=" . $row["id"] . ">Table " . $row["description"] . " </option>";
								}
							}
							?>

						</select>
					</div>
				</div>
				<input type="date" id="start" name="date" value="2022-12-01" min="2022-12-01" max="2050-12-31">
				<button style="margin:auto; position:relative;" class="btn" type="submit">Book Now</button>
			</form>
		</div>
	</div>
	<!-- reservation section ends -->

	<!-- news section start -->
	<section class="blog welcome" id="blog">
		<h1 class="heading">latest news</h1>
		<center>
			<h3 class="sub-heading"> Great articles </h3>
		</center>

		<div class="box-container">
			<div class="box">
				<div class="image">
					<img src="assets/images/post-thumb-4.jpg">
				</div>

				<div class="content">
					<h3>PROFESSIONAL LEVEL</h3>
					<p>nor again is there anyone who loves or pursues or desires to obtain pain of itself, becuase it is pain, but because occasionally circumstances occur.</p>
					<a href="#">READ MORE</a>
					<img src="assets/images/post-body-bg-1.png">
				</div>
			</div>

			<div class="box">
				<div class="image">
					<img src="assets/images/post-thumb-5.jpg">
				</div>

				<div class="content">
					<h3>FRESH FOOD GUARANTEED</h3>
					<p>nor again is there anyone who loves or pursues or desires to obtain pain of itself, becuase it is pain, but because occasionally circumstances occur.</p>
					<a href="#">READ MORE</a>
					<img src="assets/images/post-body-bg-2.png">
				</div>
			</div>

			<div class="box">
				<div class="image">
					<img src="assets/images/post-thumb-6.jpg">
				</div>

				<div class="content">
					<h3>THE MENU IS PLENTIFUL</h3>
					<p>nor again is there anyone who loves or pursues or desires to obtain pain of itself, becuase it is pain, but because occasionally circumstances occur.</p>
					<a href="#">READ MORE</a>
					<img src="assets/images/post-body-bg-3.png">
				</div>
			</div>

		</div>
	</section>
	<!-- news section ends -->


	<!-- footer section start -->
	<section class="footer">
		<img src="assets/images/logo.png" class="logo">

		<div class="container">
			<div>
				<h3>ABOUT US</h3>
				<p>Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod.</p>
			</div>

			<div>
				<h3>GET NEWS & OFFERS</h3>
				<input type="email" name="" placeholder="Enter your email">
				<ul>
					<li><a href="#"><i class="fa-brands fa-twitter"></i></a></li>
					<li><a href="#"><i class="fa-brands fa-instagram"></i></a></li>
					<li><a href="#"><i class="fa-brands fa-whatsapp"></i></a></li>
					<li><a href="#"><i class="fa-brands fa-linkedin-in"></i></a></li>
				</ul>
			</div>

			<div>
				<h3>CONTACT US</h3>
				<span>Creative Networks Tohana</span>
				<span>+ (91) 8146115525</span>
				<span>Creativenetworks001@gmail.com</span>
				<span>www.creativenetworks.in</span>
			</div>
		</div>

		<p>&copy;2022 Reserved by creative networks</p>
	</section>
	<!-- footer section end -->

	<!-- jump to top -->

	<a href="#"><button class="topbtn"><i class="fa-solid fa-angle-up"></i></button></a>










	<!--Main app js file-->
	<script src="app.js"></script>

	<!-- Swiper JS -->
	<script src="https://unpkg.com/swiper/swiper-bundle.min.js"></script>

	<!-- Initialize Swiper -->
	<script>
		var swiper = new Swiper(".home-slider", {
			spaceBetween: 30,
			centeredSlides: true,
			autoplay: {
				delay: 7500,
				disableOnInteraction: false,
			},
			pagination: {
				el: ".swiper-pagination",
				clickable: true,
			},
			loop: true,
		});
	</script>
	<script type="text/javascript">
		let menu = document.querySelector('#menu');
		let navbar = document.querySelector('.navbar');

		menu.onclick = () => {
			menu.classList.toggle('fa-times');
			navbar.classList.toggle('active');
		}
	</script>




</body>

</html>