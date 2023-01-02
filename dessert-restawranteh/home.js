
window.onload = () => {
  activeNav();
}

window.onscroll = () => {
  activeNav();
};


//nav 
function activeNav() {
  const section = document.querySelectorAll(".content > div");
  const menu = document.querySelectorAll("header nav li a");
  var scrolly = window.scrollY;
  // var fooTop= document.getElementById('Food').offsetTop - 80;
  var abTop= document.getElementById('About').offsetTop - 80;

  section.forEach((i) => {
   
    var top = i.offsetTop - 80;
    var height = i.offsetHeight;
    var id = i.getAttribute("id");


    if (scrolly >= top && scrolly < top + height) {
      menu.forEach((link) => {
        link.classList.remove("active");
        document
          .querySelector("header nav li a[href*=" + id + "]")
          .classList.add("active");
      });
    }
    else {
      if (scrolly <=abTop) {
        menu.forEach((link) => {link.classList.remove("active");});
        document
        .getElementsByClassName('home')[0]
        .classList.add("active");
      }
    }
  });


  if (scrolly >abTop - 300){
    document.getElementsByTagName('nav')[0].style.backgroundColor='var(--Grey)';
    document.getElementById('Logo').style.width='110px'
    document.getElementsByTagName('nav')[0].style.boxShadow='var(--shadow-light)';

  }
  else {
    document.getElementsByTagName('nav')[0].style.backgroundColor='';
    document.getElementById('Logo').style.width='170px';
    document.getElementsByTagName('nav')[0].style.boxShadow='none';

  }
}








//auto fill booking date as today
var date = new Date();
var currentDate = date.toISOString().slice(0,10);
var currentTime = '12:00';
document.getElementById('b-date').min = currentDate;
document.getElementById('b-date').value = currentDate;

document.getElementById('b-time').value = currentTime;



//review block
let slideIndex = 2;
showSlides(slideIndex);

function plusSlides(n) {
  showSlides(slideIndex += n);
}

function currentSlide(n) {
  showSlides(slideIndex = n);
}

function showSlides(n) {
  let i;
  let slides = document.getElementsByClassName("review");
  let dots = document.getElementsByClassName("dot");

  if (n > slides.length) {slideIndex = 1}
  if (n < 1) {slideIndex = slides.length}

  for (i = 0; i < slides.length; i++) {
    slides[i].style.display = "none";
    dots[i].classList.remove('dot-active');
  }
  
  slides[slideIndex-1].style.display = 'flex';
  dots[slideIndex-1].classList.add('dot-active');
} 





