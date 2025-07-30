import './Button.css';

interface ButtonProps {
    text: string;
    onClick?: () => void;
    type?: 'button' | 'submit' | 'reset';
    disabled?: boolean;
}

export function Button({ text, onClick, type = 'button', disabled = false }: ButtonProps) {
    return (
        <button className="custom-button" onClick={onClick} type={type} disabled={disabled}>
            {text}
        </button>
    );
}
