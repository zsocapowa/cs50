// Get form fields
document.addEventListener("change", (e) => {
	const { target } = e;
	if (!target.matches("#contact-form input")) {
		return;
	}
	e.preventDefault();
    saveFormData(target)
});


function saveFormData(target) {
    const formData = {};
    formData[target.id] = target.value;
    localStorage.setItem('formData', JSON.stringify(formData));
}


// Retrieve stored data and populate form fields when the page loads
window.addEventListener('navigate', () => {
    const location = window.location.pathname;
	if (location != '/contact') {
		return;
	}
    const storedData = localStorage.getItem('formData');

    if (storedData) {
        const formData = JSON.parse(storedData);

        nameField.value = formData.name;
        emailField.value = formData.email;
    }
});
