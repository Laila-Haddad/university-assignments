window.onscroll = () => {
  activeNav();
  stickyBar();
};
window.onload = () => {
  loadMenu();
};


//load menu items
function loadMenu() {

  fetch("food.json")
    .then((res) => {
      return res.json();
    })
    .then((data) => {

      //outputs category titles
      for (var i = 0; i < data.category.length; i++) {
        document.getElementById("Food").innerHTML += (`     
        <div id="${data.category[i].catId}">
        <div class="title">
          <hr>
          <span class="thyme1"></span>
          <h3>${data.category[i].catName}</h3>
          <span class="thyme2"></span>
          <hr>
        </div>`);

        //outputs food items for each category
        for (var j = 0; j < data.category[i].catItems.length; j++) {
          document.getElementById(data.category[i].catId).innerHTML +=
            (`<div class="item">
            <img src="${data.category[i].catItems[j].pic}">
            <div class="desc">
              <h6 class="food-name">${data.category[i].catItems[j].itemName}</h6>
              <div class="food-line"></div>
             <h6 class="food-price">${data.category[i].catItems[j].itemPrice}</h6>
              <p>${data.category[i].catItems[j].desc}</p>
            </div>
          </div>`)
        };


        document.getElementById("Food").innerHTML += (`</div> `)
      }
    });

}




//catgory bar from menu page
var cat = document.getElementById('categories');
const sticky = cat.offsetTop - 70;

function stickyBar() {
  if (window.scrollY >= sticky) {
    cat.style.position = 'fixed';
    cat.style.top = '70px';
  }
  else {
    cat.style.position = 'absolute';
    cat.style.top = '240px';
  }
}




function activeNav() {
  var scrolly = window.scrollY;
  var fooTop = document.getElementById('Food').offsetTop - 80;

  if (scrolly > fooTop - 100) {
    document.getElementsByTagName('nav')[0].style.backgroundColor = 'var(--Grey)';
    document.getElementsByTagName('nav')[0].style.boxShadow = 'var(--shadow-light)';

    document.getElementById('Logo').style.width = '110px'
    document.getElementsByClassName('landing')[0].style.backgroundImage = 'none';
    document.getElementsByClassName('landing')[0].style.boxShadow = 'none';

  }
  else {
    document.getElementsByTagName('nav')[0].style.backgroundColor = '';
    document.getElementById('Logo').style.width = '170px';
    document.getElementsByClassName('landing')[0].style.backgroundImage = 'url(Cover/cover2.webp)';
    document.getElementsByTagName('nav')[0].style.boxShadow = 'none';
    document.getElementsByClassName('landing')[0].style.boxShadow = '1px 6px 15px #00000022';

  }
}
