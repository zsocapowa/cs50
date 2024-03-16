import { loadFormData } from './contact-form.js';

// create document click that watches the nav links only
document.addEventListener("click", (e) => {
	const { target } = e;
	if (!target.matches("#navbarSupportedContent a")) {
		return;
	}
	e.preventDefault();
	urlRoute();
});

const urlRoutes = {
	404: {
		template: "/templates/404.html",
		title: "404",
	},
	"/": {
		template: "/templates/home.html",
		title: "home",
	},
	"/pmtsz": {
		template: "/templates/pmtsz.html",
		title: "pmtsz",
	},
	"/contact": {
		template: "/templates/contact.html",
		title: "contact",
	},
};

const urlRoute = (event) => {
	event = event || window.event; // get window.event if event argument not provided
	event.preventDefault();
	window.history.pushState({}, "", event.target.href);
	urlLocationHandler();
};

// create a function that handles the url location
const urlLocationHandler = async () => {
	const location = window.location.pathname; // get the url path
	// if the path length is 0, set it to primary page route
	if (location.length == 0) {
		location = "/";
	}
	// get the route object from the urlRoutes object
	const route = urlRoutes[location] || urlRoutes["404"];
	// get the html from the template
	const html = await fetch(route.template).then((response) => response.text());
	// set the content of the content div to the html
	document.getElementById("content").innerHTML = html;
	// set the title of the document to the title of the route
	document.title = route.title;

	if (location === "/contact") {
		loadFormData(); // Call the loadFormData function
		document.getElementById("contact-submit").addEventListener("click", () => localStorage.setItem("contactFormSubmitted", true));
		document.getElementById("content").innerHTML = await fetch("/templates/contact-success.html").then((response) => response.text());
	}
};

// add an event listener to the window that watches for url changes
window.onpopstate = urlLocationHandler;
// call the urlLocationHandler function to handle the initial url
window.route = urlRoute;
// call the urlLocationHandler function to handle the initial url
urlLocationHandler();
